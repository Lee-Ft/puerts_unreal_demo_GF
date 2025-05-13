// Fill out your copyright notice in the Description page of Project Settings.


#include "TsGameInstance.h"
#include "JsObject.h"
#include "UEDataBinding.hpp"

void UTsGameInstance::Init()
{
    Super::Init();
}

void UTsGameInstance::OnStart()
{
    Super::OnStart();
    //GameScript = MakeShared<puerts::FJsEnv>();
    GameScript = MakeShared<puerts::FJsEnv>(std::make_unique<puerts::DefaultJSModuleLoader>(TEXT("JavaScript")), std::make_shared<puerts::FDefaultLogger>(), 8080);
    //GameScript->WaitDebugger();
    TArray<TPair<FString, UObject*>> Arguments;
    Arguments.Add(TPair<FString, UObject*>(TEXT("GameInstance"), this));
    GameScript->Start("RetainFunction", Arguments);

    GetWorld()->GetTimerManager().SetTimer(AutoDestroyTimerHandle, FTimerDelegate::CreateUObject(this, &UTsGameInstance::OnAutoDestroy), 10, false);
}

void UTsGameInstance::Shutdown()
{
    Super::Shutdown();
    GameScript.Reset();
    RetainFunction = nullptr;
}

void UTsGameInstance::OnAutoDestroy()
{
    UE_LOG(LogTemp, Log, TEXT("JS Env Released"));
    GameScript.Reset();
}

void UTsGameInstance::SetFunc(std::function<void(float)> InFunc)
{
    RetainFunction = InFunc;
}

UsingUClass(UTsGameInstance);

struct AutoRegisterForTsGameInstance
{
    AutoRegisterForTsGameInstance()
    {
        puerts::DefineClass<UTsGameInstance>()
            .Method("SetFunc", MakeFunction(&UTsGameInstance::SetFunc))
            .Register();
    }
};

AutoRegisterForTsGameInstance _AutoRegisterForTsGameInstance_;