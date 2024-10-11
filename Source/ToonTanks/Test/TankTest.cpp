#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"

#include "../Tank.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTankTest, "ToonTest.Tank", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FTankTest::RunTest(const FString& Parameters)
{
	TObjectPtr<UWorld> World = FAutomationEditorCommonUtils::CreateNewMap();
	//World->DeltaTimeSeconds
	World->DeltaTimeSeconds=1.f;
	UE_LOG(LogTemp, Warning, TEXT("location delta seconds , %f"),World->DeltaTimeSeconds );
	{
		TObjectPtr<ATank> Tank = World->SpawnActor<ATank>();
		if(Tank)
		{
			UE_LOG(LogTemp, Warning, TEXT("location test , %s"),*Tank->GetActorLocation().ToText().ToString()  );
			
			Tank->Move(1.f);
			//UE_LOG(LogTemp, Warning, TEXT("location test , %s"),*Tank->GetActorLocation().ToText().ToString()  );

          
           	TestEqual(TEXT("Newly-spawned tank must moved 200 positions in X axis"),static_cast<float>(Tank->GetActorLocation().X), 200.f,0.f);

           	Tank->Destroy();
		}

	}
	return true;
}