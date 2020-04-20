#include "IKLibrary.h"

#include "DrawDebugHelpers.h"

FVector UIKLibrary::TraceGround(UObject* Target, const FVector& From, float RaycastMaxDistance)
{
	UWorld* World = Target->GetWorld();
	if (World)
	{
		FVector Start = From + FVector(0, 0, RaycastMaxDistance);
		FVector End = From - FVector(0, 0, RaycastMaxDistance);

		FHitResult Hit;

		FCollisionQueryParams TraceParams;

		if (World->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams))
		{
			DrawDebugPoint(Target->GetWorld(), Hit.Location, 10.0f, FColor::Yellow, false, 0.5f);

			return Hit.Location;
		}
		else
		{
			return From;
		}

	}

	return From;
}

void UIKLibrary::TraceGroundWithNormal(UObject* Target, const FVector& From, float RaycastMaxDistance, FVector &HitLocation, FVector &Normal)
{
	UWorld* World = Target->GetWorld();
	if (World)
	{

		FVector Start = From + FVector(0, 0, RaycastMaxDistance);
		FVector End = From - FVector(0, 0, RaycastMaxDistance);

		FHitResult Hit;


		FCollisionQueryParams TraceParams;

		DrawDebugLine(Target->GetWorld(), Start, End, FColor::Red, false, 0.5f, 0, 2);

		if (World->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams))
		{
			HitLocation = Hit.Location;

		}
		else
		{
			HitLocation = From;
		}
	}

	HitLocation = From;
}

void UIKLibrary::FootByGroupIK(UObject* Target, ACharacter* Character, const TArray<FName> &ListSocketName, float DistanceMaxGround, TArray<float> &IKLegs, float &HipDeplacement, TArray<FRotator> &RotateFoot)
{
	float ZPositionOfActor;

	TArray<float> DistFromGround;

	ZPositionOfActor = Character->GetActorLocation().Z - Character->GetDefaultHalfHeight();


	int index = 0;

	for (FName NameSocket : ListSocketName)
	{
		FVector PosSocket = Character->GetMesh()->GetSocketLocation(NameSocket);

		FVector HitLocation;
		FVector Normal;

		TraceGroundWithNormal(Target, PosSocket, 100.0f, HitLocation, Normal);

		RotateFoot.Push(FRotator(atan2(Normal.Y, Normal.Z), atan2(Normal.X, Normal.Z) * (-1), 0));

		//RotateFoot.Push(UKismetMathLibrary::FindLookAtRotation(Character->GetActorForwardVector(),Normal ));

		DistFromGround.Push(TraceGround(Target, PosSocket, 100.0f).Z);

		IKLegs.Push(0);

		index++;

	}

	//UE_LOG(LogTemp, Warning, TEXT("size footrotate %i"), RotateFoot.Num());

	float min = INFINITY;

	for (float Element : DistFromGround)
	{
		if (Element < min)
			min = Element;
	}

	HipDeplacement = min - ZPositionOfActor;
	HipDeplacement = abs(HipDeplacement);

	for (int i = 0; i < IKLegs.Num(); i++)
	{

		IKLegs[i] = abs(DistFromGround[i] - ZPositionOfActor) / DistanceMaxGround;

	}

}

FRotator UIKLibrary::BodyRotateIK(UObject* Target, ACharacter* Character, float DistanceFromCenterFront, float DistanceFromCenterBack)
{
	FVector ForwardVector = Character->GetActorForwardVector();

	FVector ActorLocation = Character->GetActorLocation();

	float ZPositionOfActor;

	ZPositionOfActor = Character->GetActorLocation().Z - Character->GetDefaultHalfHeight();


	float XFrontPoint = ForwardVector.X * DistanceFromCenterFront + ActorLocation.X;
	float YFrontPoint = ForwardVector.Y * DistanceFromCenterFront + ActorLocation.Y;
	float ZFrontPoint = ForwardVector.Z * DistanceFromCenterFront + ZPositionOfActor;

	FVector FrontPoint = FVector(XFrontPoint, YFrontPoint, ZFrontPoint);

	float XBackPoint = ForwardVector.X * DistanceFromCenterBack + ActorLocation.X;
	float YBackPoint = ForwardVector.Y * DistanceFromCenterBack + ActorLocation.Y;
	float ZBackPoint = ForwardVector.Z * DistanceFromCenterBack + ZPositionOfActor;

	FVector BackPoint = FVector(XBackPoint, YBackPoint, ZBackPoint);


	//DrawDebugLine(Target->GetWorld(), FrontPoint, BackPoint, FColor::Red, false, 0.5f, 0, 10);

	FVector AngleVector = TraceGround(Target, FrontPoint, 200.0f) - TraceGround(Target, BackPoint, 100.0f);

	return UKismetMathLibrary::FindLookAtRotation(AngleVector, ForwardVector);
}


float UIKLibrary::BodyHipsIK(UObject* Target, ACharacter* Character, FRotator BodyRotate, float SizeOfLeg)
{
	float ZPositionOfActor;

	FVector ActorLocation = Character->GetActorLocation();

	ZPositionOfActor = Character->GetActorLocation().Z - Character->GetDefaultHalfHeight();

	FVector NearGround = TraceGround(Target, FVector(ActorLocation.X, ActorLocation.Y, ZPositionOfActor), 100.0f);

	float DistanceFromGround = abs(NearGround.Z - ZPositionOfActor);

	//float DistanceFromGround = NearGround.Z - ZPositionOfActor;

	if (BodyRotate.Pitch < 1.0f)
	{
		return -DistanceFromGround;
	}
	else
	{
		return DistanceFromGround + SizeOfLeg;
	}


}

bool UIKLibrary::IsGrounded(UObject* Target, ACharacter* Character)
{
	FVector Start = Character->GetActorLocation();

	FVector End = Character->GetActorLocation() - FVector(0, 0, Character->GetDefaultHalfHeight() + 25);

	FHitResult Hit;

	FCollisionQueryParams TraceParams;

	return Target->GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

}

