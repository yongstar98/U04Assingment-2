#include "CAnimNotifyState_Reload.h"
#include "CWeaponInterface.h"
#include "CWeapon.h"

FString UCAnimNotifyState_Reload::GetNotifyName_Implementation() const
{
	return "Reload";
}

void UCAnimNotifyState_Reload::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp->GetOwner() == nullptr) return;

	ICWeaponInterface* ImplementedOwner = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACWeapon* Weapon = ImplementedOwner->GetWeapon();
	if (Weapon == nullptr) return;

	Weapon->Begin_Reload ();
}

void UCAnimNotifyState_Reload::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (MeshComp->GetOwner() == nullptr) return;

	ICWeaponInterface* ImplementedOwner = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACWeapon* Weapon = ImplementedOwner->GetWeapon();
	if (Weapon == nullptr) return;

	Weapon->End_Reload();
}
