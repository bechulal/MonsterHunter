#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Characters/CharacterTypes.h"
#include "Enemy.generated.h"


class UHealthBarComponent;
class UPawnSensingComponent;




UCLASS()
class MYPROJECT_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemy();

	/* Actor */
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	/* /Actor */

	/* IHitInterface */
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	/* /IHitInterface */

protected:

	virtual void BeginPlay() override;
	virtual void Die_Implementation() override;
	void SpawnSoul();
	virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual void HandleDamage(float DamageAmount) override;
	virtual void AttackEnd();

	

	UPROPERTY(BlueprintReadOnly)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;

	


private:
	/* AI Behavior */
	void InitializeEnemy();
	void CheckPatrolTarget();
	void CheckCombatTarget();
	void PatrolTimerFinished();
	void HideHealthBar();
	void ShowHealthBar();
	void LoseInterest();
	void StartPatrolling();
	void ChaseTarget();
	void ClearPatrolTimer();
	bool IsOutsideCombatRadius();
	bool IsOutsideAttackRadius();
	bool IsInsideAttackRadius();
	bool IsChasing();
	bool IsDead();
	bool IsAttacking();
	bool IsEngaged();
	void SetAttackTimer();
	void ClearAttackTimer();
	void MoveToTarget(AActor* Target);
	void SpawnDefaultWeapon();
	bool InTargetRange(AActor* Target, double Radius);

	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);

	AActor* ChoosePatrolTarget();

	UPROPERTY(EditInstanceOnly)
	AActor* PatrolTarget;


	UPROPERTY()
	class AAIController* EnemyController;

	UPROPERTY(EditInstanceOnly)
	TArray<AActor*> PatrolTargets;

	UPROPERTY(EditInstanceOnly)
	double  PatrolRadius = 200.f;

	

	FTimerHandle PatrolTimer;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWeapon> WeaponClass;


	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

	UPROPERTY(EditAnywhere)
	double CombatRadius = 1000.f;

	UPROPERTY(EditAnywhere)
	double AttackRadius = 150.f;

	UPROPERTY(EditAnywhere)
	double AcceptanceRadius = 50.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMin = 5.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMax = 10.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float PatrollingSpeed = 125.f;

	FTimerHandle AttackTimer;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMin = 0.5f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMax = 1.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float DeathLifeSpan = 8.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float ChasingSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	TSubclassOf<class ASoul> SoulClass;
};
