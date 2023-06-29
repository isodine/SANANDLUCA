#pragma once

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <appframe.h>
#include "ApplicationMain.h"
#include "Camera.h"
#include "Player/LKAclass.h"
#include "Player/SANclass.h"
#include "Player/Player.h"
#include "Damage.h"
#include "Boss.h"
#include "Slime.h"
#include "timer.h"
#include "Player/PlayerBomb.h"
#include "Player/SanBomb.h"
#include "Player/LkaBomb.h"
#include "GameMode/ModeGame.h"
#include "GameMode/ModeBoss.h"
#include "GameMode/ModeEnding.h"
#include "GameMode/ModeGameOver.h"
#include "GameMode/ModeLogo.h"
#include "GameMode/ModeStage0.h"
#include "GameMode/ModeTitle.h"
#include "Player/sanbomb.h"
#include "IronDoor.h"
#include "Electrode.h"
#include "Elevator.h"
#include "Tube.h"
#include "BossSwamp.h"


#include <string>
#include <memory>
#include <vector>

#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include <DxLib.h>
