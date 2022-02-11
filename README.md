# GAS Portfolio
언리얼 엔진4의 GameplayAbilitySystem(이하 GAS)을 사용하기 위한 프로젝트입니다.

# 목차
* [소개 영상](https://youtu.be/sdG4s10_APc)
* [구현 내용](#구현-내용)

# 구현 내용
+ [리슨 서버](#리슨-서버)
+ [인벤토리](#인벤토리)
  + [장비 교체](#장비-교체)
    + [공격 방식 변경](#공격-방식-변경)
    + [속성 변경](#속성-변경)
  + [아이템 드랍](#아이템-드랍)
+ [AttributeSet](#attributeset) 
+ [GameplayAbility](#gameplayability)
  + [공격](#공격)
    + [쿨타임](#쿨타임)
    + [데미지 처리](#데미지-처리)
  + [피격](#피격)
  + [사망](#사망)
    + [사망 시 아이템 드랍](#사망-시-아이템-드랍)
+ [GameplayCue](#gameplaycue)
  + [피격 처리](#피격-처리)

# 리슨 서버
이 프로젝트는 GAS를 효율적으로 사용하기 위해 리슨 서버의 형식으로 구현되었습니다.
GAS는 AbilitySystemComponent의 리플리케이트를 통해 어떤 동작을 실행할 때 그 동작을 리플리케이트 시켜줍니다.
![서버 생성](https://user-images.githubusercontent.com/42613341/152781984-2b002dac-4c1e-439b-81a6-87fa8ae0614e.PNG)
<!-- <img src="https://user-images.githubusercontent.com/42613341/152781984-2b002dac-4c1e-439b-81a6-87fa8ae0614e.PNG"  width="400" height="300"/> -->
![서버접속2](https://user-images.githubusercontent.com/42613341/152949573-e5a2e257-b548-4445-9352-730202f53ac5.gif)
![서버접속3](https://user-images.githubusercontent.com/42613341/152949637-9dd703de-cfdd-4e1e-9786-f94963083087.gif)


# 인벤토리
인벤토리는 무기와 장신구를 변경할 수 있습니다.
I키를 누르면 인벤토리가 활성화 됩니다.
좌상단의 수치는 아이템을 장착하거나, 피격, 회복을 하는 등의 동작을 통해 변경되는 수치입니다.
![인벤토리1](https://user-images.githubusercontent.com/42613341/152953495-f70254f3-8c0b-4af1-a89a-0f626999deec.PNG)

아이템의 정보는 플레이어 컨트롤러가 지니고 있으며, 인벤토리를 호출할 때 플레이어 컨트롤러가 지니고 있는 아이템의 맵을 이용해 인벤토리에 배치해 보여줍니다. 
![인벤토리](https://user-images.githubusercontent.com/42613341/152953934-6899e962-0c7e-4da6-818f-c46e83f50095.PNG)

아이템의 배치를 변경할 수 있습니다.
![인벤토리 위치 변경](https://user-images.githubusercontent.com/42613341/152954356-79f1152b-5402-4591-b967-28fd86b036ec.gif)

아이템 칸은 각각의 위젯 블루프린트로 구성되어 있으며, 드래그 앤 드랍으로 이동할 수 있습니다.
![위치변경1](https://user-images.githubusercontent.com/42613341/152955318-85dbb904-1beb-4d7f-a22b-0f30a0cfbfc8.PNG)
```c++
void ACPP_CharacterController::ChangeItem()
{
	if (Inventory != nullptr)
	{
		Inventory->ChangeItem();
	}
}
```
![위치변경2](https://user-images.githubusercontent.com/42613341/152955939-6b1f2148-e37d-42c8-898a-088fdd91cb0f.PNG)

## 장비 교체
장비는 드래그 앤 드랍으로 교체할 수 있습니다.
![장비변경1](https://user-images.githubusercontent.com/42613341/152956237-60990447-fda4-4b12-b147-7be9ab02d67b.gif)

장착한 무기의 기존 아이템 칸은 공란으로 변경하거나 원래 장착되어 있던 아이템의 정보로 변경합니다.
![무기변경1](https://user-images.githubusercontent.com/42613341/152956363-346e2c94-650a-420a-a3bc-51d80f4d0295.PNG)

### 공격 방식 변경
무기를 교체하면 공격 방식이 변경됩니다.

##### 검
![무기1](https://user-images.githubusercontent.com/42613341/152961143-88639198-d4e6-4e2a-9a18-15b7fbb8327d.gif)

##### 마법
![Honeycam 2022-02-08 18-46-03](https://user-images.githubusercontent.com/42613341/152961218-1b32145a-adf2-4d64-b3f4-bcc20ff39d4c.gif)

무기를 변경 시 애니메이션을 바꾸고 공격 시 비교할  변경합니다.
![무기2](https://user-images.githubusercontent.com/42613341/152961600-53023681-227e-46a4-97fa-d4618995ea39.PNG)

![무기3](https://user-images.githubusercontent.com/42613341/152962397-ecac0659-8c71-4ec1-b59a-a06dd9b01d1c.PNG)


### 속성 변경
장신구를 교체하면 공격 속성이 변경됩니다.
![속성1](https://user-images.githubusercontent.com/42613341/152963414-fd99836b-d32c-4535-b85c-916ecf3cbf87.gif)
![속성변경2](https://user-images.githubusercontent.com/42613341/152963442-10ce7f21-3110-4ca7-8fcb-47d038113547.gif)
##### 검
검의 경우는 직접 트레일이 변경됩니다.
![속성변경 1](https://user-images.githubusercontent.com/42613341/152965112-10bfcf70-61e6-4239-97c6-96a025a5d6c8.PNG)


##### 마법
마법은 공격버튼을 누르면 작동되는 어빌리티가 달라집니다.
![속성변경 2](https://user-images.githubusercontent.com/42613341/152965196-534180f8-0a93-4e09-bb59-dd69c2993ae7.PNG)


## 아이템 드랍
아이템을 드랍할 수 있습니다.
![아이템드랍1](https://user-images.githubusercontent.com/42613341/152965995-4070ebe8-a81e-4ab5-903f-a716391e0bf4.gif)

![아이템드랍2](https://user-images.githubusercontent.com/42613341/152966005-8948089c-1527-4aaa-9484-f2f1ff3ff0a1.gif)

아이템을 인벤토리에서 아이템칸이 아닌 곳에 드랍을 하게 되면 아이템을 맵에 스폰하고 플레이어컨트롤러에 존재하는 아이템을 삭제합니다.

필드의 아이템은 리플리케이트 되어 다른 플레이어가 아이템을 좌클릭하여 획득하면 모든 클라이언트에서 필드의 아이템이 삭제됩니다.

# AttributeSet

# GameplayEffect

# GameplayAbility
GAS의 중점인 Ability(이하 어빌리티)입니다.
공격, 피격, 사망등의 동작은 어빌리티로 관리됩니다.

![어빌리티1](https://user-images.githubusercontent.com/42613341/153562742-2a10fdc4-c6be-4776-b3d4-3c770fc6d709.PNG)

어빌리티는 GameplayTask 라는 것을 사용해 흐름을 설정할 수 있습니다.
이 프로젝트에서는 사망 어빌리티가 끝났을 때 아이템을 드랍하는 것만 사용하고 있습니다.

어빌리티는 GameplayTag를 사용해 어빌리티의 동작을 관리할 수 있습니다.
GameplayTag를 이용해 어빌리티를 실행시키거나, 어빌리티의 실행을 차단, 실행되고 있는 어빌리티를 캔슬할 수 있습니다.

게임 도중에 어빌리티를 삭제하거나 부여하는 등의 관리가 가능하나 이 프로젝트에서는 폰을 소유하게 되었을 때 함수를 사용해 어빌리티를 부여하고 있습니다.


```c++
void ASharedCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComp) {
		AbilitySystemComp->InitAbilityActorInfo(this, this);

		InitializeAttributes();
		GiveAbilities();
	}
}
```

![어빌리티 부여](https://user-images.githubusercontent.com/42613341/153564197-c62c4563-3133-42e8-92da-34c8eeaa524f.PNG)

```c++
void ASharedCharacter::GiveAbilities()
{
	if (HasAuthority() && AbilitySystemComp && DefaultAbilities.Num() > 0)
	{
		for (TSubclassOf<UGASGameplayAbility>& StartupAbility : DefaultAbilities)
		{
			AbilitySystemComp->GiveAbility(
				FGameplayAbilitySpec(StartupAbility, 1, INDEX_NONE, this));
		}

	}
}
```

## 공격
공격은 AbilitySystemComponent(이하 ASC)에 등록된 공격 어빌리티를 실행하는 것으로 동작합니다.
ASC는 리플리케이트가 되어, 어빌리티를 모든 클라이언트에서 동일하게 동작하도록 합니다.

공격 어빌리티는 동작되게 되면 몽타주를 실행하는데 만약 마법 공격이라면 투사체를 스폰합니다.
투사체 또한 리플리케이트 되어 서버에서 데미지 처리를 하게 됩니다.

![어빌리티2](https://user-images.githubusercontent.com/42613341/153564691-b145a8ea-8a34-4fac-9dc5-37a495ba4213.PNG)

어빌리티의 설정에 리플리케이트 관련 옵션이 있으나 이는 모두에게 작동하도록 하는 것과는 약간 다른 측면이 있으므로, ASC에서 실행을 하게 해 ASC를 리플리케이트 하는 것으로 네트워킹을 하고 있습니다.

### 쿨타임
GameplayEffect를 사용해 쿨타임을 설정할 수 있습니다.

![쿨타임](https://user-images.githubusercontent.com/42613341/153565474-4ce3ab71-f37d-4ae5-bdee-dc2dc6b3adf2.PNG)

0.7초로 이펙트의 지속시간을 부여하고, 이펙트가 지속이 되어있는 동안 CoolDown.Attack.Sword의 GameplayTag를 부여합니다.

![쿨타임 2](https://user-images.githubusercontent.com/42613341/153565809-be7e68f0-e5df-4c62-a549-ab9f44f7cebb.gif)

[GamePlayAbility](#gameplayability)의 첫번째 이미지에 있는 CommitAbility에서 쿨타임과 코스트 등의 처리를 할 수 있습니다.

### 데미지 처리
GameplayEffect를 사용해 데미지 처리를 합니다.

![데미지처리1](https://user-images.githubusercontent.com/42613341/153568780-888a13b5-4ebb-4cf7-a0c6-310f53a35844.PNG) 
###### 프로젝트 내의 ANS_SwordAttack

피격 대상이 지니고 있는 ASC를 타겟으로 특정 GameplayEffect를 수행합니다.
이 경우는 데미지를 처리해야 하니 GE_GetDamage를 수행합니다.

![데미지처리2](https://user-images.githubusercontent.com/42613341/153569880-be6e493a-b8be-4b2f-b6c8-601df4ae8660.PNG)

이 [게임플레이 이펙트](#gameplayeffect) 에서는 데미지의 처리를 위해 데미지 계산기를 사용합니다.

데미지 계산기는 현재의 [어트리뷰트](#attributeset)값을 이용해 본인의 공격력과 타겟의 방어력을 받아와 공격력 - 방어력의 공식으로 데미지를 계산합니다.

그리고 특정 약점 속성으로 공격을 했다면 추가 데미지를 입힙니다.

## 피격
피격시 캐릭터에 GameplayTag를 부여합니다.

이 프로젝트에서는 공격 시 피격을 하면 그 공격 모션이 캔슬되고 피격몽타주를 실행하게 됩니다.

## 사망
사망 시 모든 모션을 종료하고 사망 몽타주를 바로 실행합니다.

사망 몽타주의 실행이 끝나면 아이템을 일정 확률로 드랍합니다.

### 사망 시 아이템 드랍
데이터 테이블에 작성 되어있는 아이템 중 하나를 랜덤으로 드랍합니다.
공격력 등의 수치는 드랍 시 랜덤으로 설정됩니다.

# GameplayCue
GameplayAbility 혹은 GameplayEffect의 처리 후 작동됩니다.
이 프로젝트에서는 데미지 계산 후 관련 이미터와 사운드의 스폰에 사용되었습니다.

## 피격 처리
데미지 계산 이후 작동됩니다.





                                                                                                                                         
