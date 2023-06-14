// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPawn.h"

#include "Animation/AnimInstanceProxy.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


// Sets default values
AMovingPawn::AMovingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sphere Collision
	USphereComponent* SphereComponent =
		CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(4.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	
	// Static Mesh
	UStaticMeshComponent* StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	StaticMesh->SetupAttachment(SphereComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> VisualAsset(TEXT("/Engine/EditorMeshes/EditorSphere"));
	if (VisualAsset.Succeeded())
	{
		StaticMesh->SetStaticMesh(VisualAsset.Object);
		StaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		StaticMesh->SetWorldScale3D(FVector(1.0f));
	}

	
	// Spring Arm
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeLocation(FVector(-45.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;
	
	// Camera
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// Make player possess this actor
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Movement Component
	MovementComponent = CreateDefaultSubobject<UCustomPawnMovementComponent>(
		TEXT("CustomMovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;
ntext 
}

void AMovingPawn::OnConstruction(const FTransform& Transform)
{
	UE_LOG(LogTemp, Display, TEXT("OnConstruction"));
}

// Called when the game starts or when spawned
void AMovingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMovingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// PlayerInputComponent->BindAction("ParticleToggle", IE_Pressed, this, &ACollidingPawn::ParticleToggle);
	// PlayerInputComponent->BindAxis("MoveForward", this, &ACollidingPawn::MoveForward);
	// PlayerInputComponent->BindAxis("MoveRight", this, &ACollidingPawn::MoveRight);
	// PlayerInputComponent->BindAxis("Turn", this, &ACollidingPawn::Turn);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (InputActions)
	{
		EnhancedInput->BindAction(InputActions->MoveForward, ETriggerEvent::Triggered, this, &AMovingPawn::MoveForward);
	}
}

UPawnMovementComponent* AMovingPawn::GetMovementComponent() const
{
	return MovementComponent;
}

void AMovingPawn::MoveForward(const FInputActionValue& Value)
{
	if (MovementComponent && (MovementComponent->UpdatedComponent == RootComponent))
	{
		float X = Value.Get<FVector2d>().X;
		float Y = Value.Get<FVector2d>().Y;
		UE_LOG(LogTemp, Display, TEXT("X = %f, Y = %f"), X, Y);
		MovementComponent->AddInputVector(GetActorForwardVector() * Y);
	}
}

