// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_GameModeBase.h"

AGM_GameModeBase::AGM_GameModeBase()
{
    static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/A_DevFolder/Characters/Playable/Controller/BP_PlayerController.BP_PlayerController_C"));
    if (PlayerControllerBPClass.Class != NULL)
    {
        PlayerControllerClass = PlayerControllerBPClass.Class;
    }

    static ConstructorHelpers::FClassFinder<APawn> RevenantBPClass(TEXT("/Game/A_DevFolder/Characters/Playable/Revenant/BP_Revenant.BP_Revenant_C"));
    if (RevenantBPClass.Class != NULL)
    {
        DefaultPawnClass = RevenantBPClass.Class;
    }
}
