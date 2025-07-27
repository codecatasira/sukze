#include "HealingItem.h"
#include "SpartaCharacter.h"

AHealingItem::AHealingItem()
{
    HealAmount = 20.0f;
    ItemType = "Healing";
}

void AHealingItem::ActivateItem(AActor* Activator)
{
    Super::ActivateItem(Activator);

    if (Activator && Activator->ActorHasTag("Player"))
    {
        if (ASpartaCharacter* PlayerCharacter = Cast<ASpartaCharacter>(Activator))
        {
            // 원래 있던 체력 회복
            PlayerCharacter->AddHealth(HealAmount);

            // 디버프 - 5초 동안 이동 속도 50% 감소
            PlayerCharacter->ApplySpeedDebuff(5.0f, 0.5f);
        }

        DestroyItem();
    }
}