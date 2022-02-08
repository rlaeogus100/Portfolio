# GAS Portfolio
언리얼 엔진4의 GameplayAbilitySystem(이하 GAS)을 사용하기 위한 프로젝트.

# 목차
* [소개 영상](https://youtu.be/sdG4s10_APc)
* [구현 내용](https://github.com/rlaeogus100/Portfolio/blob/main/README.md#구현-내용)

# 구현 내용
+ [리슨 서버](https://github.com/rlaeogus100/Portfolio/blob/main/README.md#리슨-서버)
+ [인벤토리](https://github.com/rlaeogus100/Portfolio/blob/main/README.md#인벤토리)
  + [장비 교체](https://github.com/rlaeogus100/Portfolio/blob/main/README.md#장비-교체)
    + [공격 방식 변경](https://github.com/rlaeogus100/Portfolio/blob/main/README.md#공격-방식-변경)
    + [속성 변경](https://github.com/rlaeogus100/Portfolio/blob/main/README.md#속성-변경)
  + [아이템 드랍](https://github.com/rlaeogus100/Portfolio/blob/main/README.md#아이템-드랍)
+ [GameplayAbility](https://github.com/rlaeogus100/Portfolio/blob/main/README.md#GameplayAbility)
  + [공격](https://github.com/rlaeogus100/Portfolio/blob/main/README.md#공격)
    + [쿨타임](https://github.com/rlaeogus100/Portfolio/blob/main/README.md#쿨타임)
    + [데미지 처리](https://github.com/rlaeogus100/Portfolio/blob/main/README.md#데미지-처리)
  + [피격](https://github.com/rlaeogus100/Portfolio/blob/main/README.md#피격)
  + [사망](https://github.com/rlaeogus100/Portfolio/blob/main/README.md#사망)
    + [사망 시 아이템 드랍](https://github.com/rlaeogus100/Portfolio/blob/main/README.md#사망-시-아이템-드랍)
+ [GameplayCue](https://github.com/rlaeogus100/Portfolio/blob/main/README.md#GameplayCue)
  + [피격 처리](https://github.com/rlaeogus100/Portfolio/blob/main/README.md#피격-처리)

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
```
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

# GameplayAbility
GAS의 중점인 Ability(이하 어빌리티)입니다.
공격, 피격, 사망등의 동작은 어빌리티로 관리됩니다.

어빌리티는 GameplayTask 라는 것을 사용해 흐름을 설정할 수 있습니다.
하지만 이 프로젝트에서는 사망 어빌리티가 끝났을 때 아이템을 드랍하는 것만 사용하고 있습니다.

어빌리티는 GameplayTag를 사용해 어빌리티의 동작을 관리할 수 있습니다.
GameplayTag를 이용해 어빌리티를 실행시키거나, 어빌리티의 실행을 차단, 실행되고 있는 어빌리티를 캔슬할 수 있습니다.

## 공격
공격은 AbilitySystemComponent(이하 ASC)에 등록된 공격 어빌리티를 실행하는 것으로 동작합니다.
ASC는 리플리케이트가 되어, 어빌리티를 모든 클라이언트에서 동일하게 동작하도록 합니다.

공격 어빌리티는 동작되게 되면 몽타주를 실행하는데 만약 마법 공격이라면 투사체를 스폰합니다.
투사체 또한 리플리케이트 되어 서버에서 데미지 처리를 하게 됩니다.

### 쿨타임
GameplayEffect를 사용해 쿨타임을 설정할 수 있습니다.

### 데미지 처리
GameplayEffect를 사용해 데미지 처리를 합니다.

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





                                                                                                                                         
