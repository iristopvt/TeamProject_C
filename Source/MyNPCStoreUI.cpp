// Fill out your copyright notice in the Description page of Project Settings.



#include "MyNPCStoreUI.h"

#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "MyNPCStoreComponent.h"
#include "MyNPCItem.h"
#include "MyPlayer.h"
#include "MyInvenComponent.h"

#include "MyPlayer.h"
#include "MyItem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "MyInvenUI.h"


void UMyNPCStoreUI::NativeConstruct()
{
    Super::NativeConstruct();

    auto array = NPCSlotGrid->GetAllChildren();

    for (auto widget : array)
    {
        auto Btn = Cast<UButton>(widget);
        if (Btn)
        {
            _NPCslotBtns.Add(Btn);
            _NPCslotBtnImages.Add(Cast<UImage>(Btn->GetChildAt(0)));
        }
    }


    if (npItem == nullptr)
    {
        npItem = GetWorld()->SpawnActor<AMyNPCItem>();
        if (npItem)
        {
            SetNPCItems(npItem->_ItemData);
        }

    }


    if (NPCSlotBtn_1)
    {
        NPCSlotBtn_1->OnClicked.AddDynamic(this, &UMyNPCStoreUI::checkbtn1);
    }
    if (NPCSlotBtn_2)
    {
        NPCSlotBtn_2->OnClicked.AddDynamic(this, &UMyNPCStoreUI::checkbtn2);
    }
    if (NPCSlotBtn_3)
    {
        NPCSlotBtn_3->OnClicked.AddDynamic(this, &UMyNPCStoreUI::checkbtn3);
    }

    if (BuyBtn)
    {
        BuyBtn->OnClicked.AddDynamic(this, &UMyNPCStoreUI::Buyclick);
    }

    Player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));

}


void UMyNPCStoreUI::SetNPCItems(const TArray<FItemData>& Items)
{

    _Items = Items;


    for (int32 i = 0; i < _Items.Num(); ++i)
    {
        if (_NPCslotBtnImages.IsValidIndex(i) && _Items.IsValidIndex(i))
        {
            UTexture2D* ItemTexture = _Items[i].ItemTexture;
            if (ItemTexture)
            {
                _NPCslotBtnImages[i]->SetBrushFromTexture(ItemTexture);
            }
        }
    }


}

void UMyNPCStoreUI::Buyclick()
{

    if (butncheck == true)
    {
        UE_LOG(LogTemp, Error, TEXT("true check"));

        if (Player)
        {
            if (_Items.IsValidIndex(SelectedItemIndex))
            {
                const FItemData& SelectedItemData = _Items[SelectedItemIndex];

                AMyNPCItem* NewItem = GetWorld()->SpawnActor<AMyNPCItem>();
                if (NewItem)
                {
                    NewItem->_itemId = SelectedItemData.ItemId;

                    Player->_invenCom->AddItem(NewItem);
                    UE_LOG(LogTemp, Error, TEXT("Item add"));
                }

            }
            butncheck = false;
        }
    }
}
void UMyNPCStoreUI::checkbtn1()
{
    butncheck = true;
    SelectedItemIndex = 0;
    UE_LOG(LogTemp, Error, TEXT("1 item check"));
}
void UMyNPCStoreUI::checkbtn2()
{
    butncheck = true;
    SelectedItemIndex = 1;
    UE_LOG(LogTemp, Error, TEXT("2 item check"));
}
void UMyNPCStoreUI::checkbtn3()
{
    butncheck = true;
    SelectedItemIndex = 2;
    UE_LOG(LogTemp, Error, TEXT("3 item check"));
}


