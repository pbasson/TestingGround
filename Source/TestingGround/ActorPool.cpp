//PROJECT: Testing Grounds
//AUTHOR: Preetpal Basson
//DESCRIPTION:

#include "ActorPool.h"


UActorPool::UActorPool()
{

	PrimaryComponentTick.bCanEverTick = true;
}

void UActorPool::BeginPlay()
{
	Super::BeginPlay();
	
}

void UActorPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

AActor * UActorPool::Checkout()
{
	if (ThePool.Num() == 0)
    { return nullptr; }

	return ThePool.Pop();
}

void UActorPool::ReturnActor(AActor* ActorToReturn)
{
	AddActor(ActorToReturn);
}

void UActorPool::AddActor(AActor* ActorToAdd)
{
	ThePool.Push(ActorToAdd);
}
