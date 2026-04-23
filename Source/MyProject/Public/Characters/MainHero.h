// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "Interfaces/PickupInterface.h"
#include "CharacterTypes.h"
#include "MainHero.generated.h"

class USlashOverlay;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class ARealItem;
class UAnimMontage;
class AWeapon;
class ASoul;
class ATreasure;

UCLASS()
class MYPROJECT_API AMainHero : public ABaseCharacter , public IPickupInterface
{
	GENERATED_BODY()

public:
	
	AMainHero();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;

protected:
	
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* HeroContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* EquipAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* DodgeAction;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Hair;

	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Eyebrows;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* DodgeMontage;

	/*
	  Input functions
	*/
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Equip();
	virtual void Attack() override;
	void Dodge();
	bool IsOccupied();
	bool HasEnoughStamina();
	virtual bool CanAttack() override;
	void EquipWeapon(AWeapon* Weapon );

	/*
	 Animation Montage Functions
	*/
	
	virtual void AttackEnd() override;
	void PlayEquipMontage(const FName& SectionName);
	void PlayDodgeMontage();
	bool CanDisarm();
	bool CanArm();
	void Disarm();
	void Arm();
	virtual void Die_Implementation() override;

	UFUNCTION(BlueprintCallable)
	void DodgeEnd();

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToBack();

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToHand();

	UFUNCTION(BlueprintCallable)
	void FinishedEquipping();

	UFUNCTION(BlueprintCallable)
	void HitReactEnd();

private:

	bool IsUnoccupied();
	void InitializeSlashOverlay();
	void SetHealthHud();

	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_UnOccupied;

	UPROPERTY(VisibleInstanceOnly)
	ARealItem* OverlappingItem;

	UPROPERTY()
	USlashOverlay* SlashOverlay;

	

public:
	virtual void SetOverlappingItem(class ARealItem* Item) override;
	virtual void AddSouls(ASoul* Soul) override;
	virtual void AddGold(ATreasure* Treasure) override;
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	FORCEINLINE EActionState GetActionState() const { return ActionState; }
};
  