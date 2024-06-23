#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon.generated.h"

class USkeletalMeshComponent;
class ACharacter;
class UAnimMontage;
class ACBullet;
class UParticleSystem;
class USoundCue;
class UDecalComponent;
class UMaterialInstanceConstant;
class UStaticMeshComponent;

DECLARE_DELEGATE_TwoParams(FBulletsCount, int32, int32);

UCLASS()
class THIRDPERSONCPP_API ACWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE bool IsEquipped() { return bEquipped; }
	FORCEINLINE bool IsEquipping() { return bEquipping; }
	FORCEINLINE bool IsAiming() { return bAiming; }
	
	FORCEINLINE bool IsFiring() { return bFiring; }//
	FORCEINLINE bool IsAutoFire() { return bAutoFire; }
	FORCEINLINE bool IsReloading() { return bReloading; }
	FORCEINLINE int32 GetMaxBullets() { return MaxBullets; }
	FORCEINLINE int32 GetCurrentBullets() { return CurrentBullets; }

	FORCEINLINE USkeletalMeshComponent* GetMesh() { return MeshComp; }

	void ToggleAutoFire();

	void Begin_Aiming();
	void End_Aiming();

	void Begin_Fire();
	void End_Fire();

	UFUNCTION()
	void Firing();

	void Equip();
	void Begin_Equip();
	void End_Equip();

	void Unequip();
	void Begin_Unequip();
	void End_Unequip();

	void Relaod();
	void Begin_Reload();
	void End_Reload();

	void ReloadOn();
	void ReloadOff();

private:
	UPROPERTY(EditDefaultsOnly, Category = "BulletClass")
	TSubclassOf<ACBullet> BulletClass;

	UPROPERTY(EditDefaultsOnly, Category = "BulletClass")
	int32 MaxBullets;


	UPROPERTY(EditDefaultsOnly, Category = "AutoFire")
	float FireInterval;

	UPROPERTY(EditDefaultsOnly, Category = "AutoFire")
	float PitchSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName HolsterSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName HandSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* UnequipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* ReloadMontage;

	UPROPERTY(EditDefaultsOnly, Category = "CameraShake")
	TSubclassOf<UCameraShake> CameraShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Decal")
	UMaterialInstanceConstant* Decal;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* MuzzleParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* EjectParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ImpactParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	USoundCue* FireSound;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UMaterialInstanceConstant* DecalMaterial;

public:
	FBulletsCount OnBulletsCount;

private:
	UPROPERTY(VisibleDefaultsOnly)
	USkeletalMeshComponent* MeshComp;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* EmtyMagazineComp;

private:
	ACharacter* OwnerCharacter;

	bool bEquipped;
	bool bEquipping;
	bool bAiming;
	bool bFiring;
	bool bAutoFire;
	bool bReloading;

	float CurrentPitch;
	int32 CurrentBullets;
	FTimerHandle AutoTimerHandle;

	
};
