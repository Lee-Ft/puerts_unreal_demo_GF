import * as UE from 'ue'
import {$ref, $unref, $set, argv, on, toManualReleaseDelegate, releaseManualReleaseDelegate, blueprint} from 'puerts';

let gameInstance = (argv.getByName("GameInstance") as UE.TsGameInstance);

// 构造一个能被持有的函数
function TestFunc(i) {
    console.log(i);
}

// 持有函数
gameInstance.SetFunc(TestFunc);
