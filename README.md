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
  + [피격]
  + [사망]
    + [사망 시 아이템 드랍] 
+ [GameplayCue]
  + [피격 처리]

# 리슨 서버
이 프로젝트는 GAS를 효율적으로 사용하기 위해 리슨 서버의 형식으로 구현되었습니다.
![서버 생성](https://user-images.githubusercontent.com/42613341/152781984-2b002dac-4c1e-439b-81a6-87fa8ae0614e.PNG)
<!-- <img src="https://user-images.githubusercontent.com/42613341/152781984-2b002dac-4c1e-439b-81a6-87fa8ae0614e.PNG"  width="400" height="300"/> -->
<!-- 서버 들어가는 이미지 -->

# 인벤토리
인벤토리는 무기와 장신구를 변경할 수 있습니다.
<!-- 인벤토리  -->

## 장비 교체
장비는 드래그 앤 드랍으로 교체할 수 있습니다.

### 공격 방식 변경
무기를 교체하면 공격 방식이 변경됩니다.

### 속성 변경
장신구를 교체하면 공격 속성이 변경됩니다.

## 아이템 드랍
아이템을 드랍할 수 있습니다.

# GameplayAbility
GAS의 중점인 Ability(이하 어빌리티)입니다.
공격, 피격, 사망등의 동작은 어빌리티로 관리됩니다.

어빌리티는 GameplayTask 라는 것을 사용해 흐름을 설정할 수 있습니다.
하지만 이 프로젝트에서는 사망 어빌리티가 끝났을 때 아이템을 드랍하는 것만 사용하고 있습니다.

## 공격
공격은 AbilitySystemComponent(이하 ASC)에 등록된 공격 어빌리티를 실행하는 것으로 동작합니다.
ASC는 리플리케이트가 되어, 어빌리티를 모든 클라이언트에서 동일하게 동작하도록 합니다.

공격 어빌리티는 동작되게 되면 몽타주를 실행하는데 만약 마법 공격이라면 투사체를 스폰합니다.
투사체 또한 리플리케이트 되어 서버에서 데미지 처리를 하게 됩니다.

### 쿨타임
GameplayEffect를 사용해 쿨타임을 설정할 수 있습니다.






                                                                                                                                         
