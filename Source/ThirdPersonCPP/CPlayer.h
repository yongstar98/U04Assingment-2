#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CWeaponInterface.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMaterialInstanceDynamic;
class ACWeapon;
class UCCrossHairWidget;
class UCWeaponWidget;

UCLASS()
class THIRDPERSONCPP_API ACPlayer : public ACharacter, public ICWeaponInterface
{
	GENERATED_BODY()

public:
	ACPlayer();

	UFUNCTION(Exec)
	void ChangeSpeed(float InMoveSpeed = 400.f);

	FORCEINLINE ACWeapon* GetWeapon() override { return Weapon; }
	virtual void GetAimInfo(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDirection) override;
	virtual void OnTarget() override;
	virtual void OffTarget() override;

	void ReloadMagazine();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnSprint();
	void OffSprint();

	void ToggleEquip();

	void OnAim();
	void OffAim();

	void OnFire();
	void OffFire();

	void OnAutoFire();

public:
	UFUNCTION(BlueprintCallable)
	void SetBodyColor(FLinearColor InBodyColor, FLinearColor InLogoColor);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void Begin_Zoom();

	UFUNCTION(BlueprintImplementableEvent)
	void End_Zoom();

public:
	UFUNCTION()
	void CallCountBullets(int32 MaxBullets, int32 CurrnetBullets);


protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UCameraComponent* CameraComp;

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponClass")
	TSubclassOf<ACWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "WidgetClass")
	TSubclassOf<UCCrossHairWidget> CrossHairWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "WidgetClass")
	TSubclassOf<UCWeaponWidget> WeaponWidgetClass;

private:
	UMaterialInstanceDynamic* BodyMaterial;
	UMaterialInstanceDynamic* LogoMaterial;

	ACWeapon* Weapon;
	
	UCCrossHairWidget* CrossHairWidget;
	UCWeaponWidget* WeaponWidget;
};
