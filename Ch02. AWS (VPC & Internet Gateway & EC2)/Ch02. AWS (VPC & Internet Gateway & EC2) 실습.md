# Ch02. AWS (VPC & Internet Gateway & EC2) 실습

## Previous Post

[Ch02. AWS (VPC & Internet Gateway & EC2)](https://oxdjww.tistory.com/entry/Ch02-AWS-VPC-Internet-Gateway-EC2)

<br>  

## Overview

```
1. VPC를 이용한 EC2 구축
2. 보안 그룹 생성하기
3. EC2 생성하기
4. 탄력적 IP 설정하기
5. IntelliJ 원격접속
6. VSCode 원격접속
7. NGINX test
```

  <br>

## 1\. VPC를 이용한 EC2 구축

1.  AWS에 로그인 후, `VPC`를 검색하여 생성하기를 누르면 다음과 같은 화면을 볼 수 있다.  
    ![1](https://github.com/oxdjww/server-study/assets/102507306/7b3fc31c-209a-43c3-8f8a-b6938fe7faf5)
    a. 이름은 자유롭게 설정한다.  
    b. `VPC`의 `CIDR`을 `10.0.0.0/16`으로 설정하고, 이를 나중에 `서브넷`으로 나눌 것이다.  
    c. 나머지 옵션은 사진과 같이 설정해준다.  
    d. 그리고 생성해준다.
2.  목차에서 `서브넷`을 선택한다.  
    <img width="257" alt="2" src="https://github.com/oxdjww/server-study/assets/102507306/3153d455-c7ab-40b1-b021-5d37605a8110">

3.  `VPC`의 서브넷을 생성하는 과정이다.  
    a. 아까 만든 `VPC`의 `VPC ID`를 선택해준다.  
    <img width="727" alt="3" src="https://github.com/oxdjww/server-study/assets/102507306/89b011f2-b805-4e18-9a16-1e552af51bad">

    b. 이름은 자유롭게 지정한다.  
    c. 필자는 `subnet1`을 나중에 `public subnet`으로 활용하고, subnet2를 `private subnet`으로 하려한다.  
    d. 서브넷을 여러개 생성할 경우 각 서브넷은 생성 순서대로 `10.0.1.0/24`, `10.0.2.0/24`, `10.0.3.0/24` ...  
    <img width="804" alt="4" src="https://github.com/oxdjww/server-study/assets/102507306/e165581f-f736-4ffe-b64d-39ab71c8dbaf">

4.  이제 `umc-tete-subnet1`을 `public subnet`으로 쓰기 위해 `Internet Gateway`를 연결해줄 차례이다.  
    a. 목차에서 `Interntet Gateway`를 선택한다.  
    <img width="237" alt="5" src="https://github.com/oxdjww/server-study/assets/102507306/44b38197-d48a-4e79-b2b3-651165b59881">

    b. 이름은 자유롭게 설정한다. 필자는 `umc-tete-ig`로 설정하고 생성해주었다.  
    <img width="868" alt="6" src="https://github.com/oxdjww/server-study/assets/102507306/2c9e681e-865c-4415-9599-ae3e021da08f">

    c. 생성을 클릭하고 나면, 상단에 뜨는 팝업 `VPC와 연결`을 클릭하여 생성한 `Internet Gateway`를 아까 만든 `VPC`와 연결해줄 것이다.  
    <img width="1170" alt="7" src="https://github.com/oxdjww/server-study/assets/102507306/b8873884-6e3e-432f-be54-ec71e512f146">

5.  `라우팅 테이블`을 설정하여, `private subnet`에서 외부와 통신하고 싶을 때 `Internet Gateway`로 패킷이 라우팅되도록 해야한다.  
    a. 목차에서 `라우팅 테이블`을 선택한다.  
    <img width="817" alt="8" src="https://github.com/oxdjww/server-study/assets/102507306/20dbd367-8ac7-4786-a95f-0cfead745b9e">

    b. 아까 만든 `VPC`의 라우팅 테이블을 선택한다.  
    <img width="1169" alt="9" src="https://github.com/oxdjww/server-study/assets/102507306/07a85290-71fb-4cf9-a53a-eecd80868870">

    c. `라우팅 편집`을 이용해, 외부의 모든 IP를 나타내는 `0.0.0.0/0`으로 향할 때 아까 만든 `umc-tete-ig`로 라우팅되도록 설정한다.  
    <img width="1396" alt="10" src="https://github.com/oxdjww/server-study/assets/102507306/6e82827d-3de4-410c-83db-a9382a9cbe5a">
    <img width="1385" alt="11" src="https://github.com/oxdjww/server-study/assets/102507306/68008aa7-0043-4231-b3e6-deb94ea17be0">
    
    d. 설정 완료  
    <img width="441" alt="12" src="https://github.com/oxdjww/server-study/assets/102507306/3e3e4830-73b5-4c9c-8eaa-bd4b65f2b055">

6.  그리고 설정이 바뀐 `라우팅 테이블`을 서브넷(`public subnet`으으로 설정할 `umc-tete-subnet1`)과 연결해준다.  
    <img width="1386" alt="14" src="https://github.com/oxdjww/server-study/assets/102507306/f2dad2d2-4e11-4a75-8e37-a3e435e31b06">
    <img width="1137" alt="13" src="https://github.com/oxdjww/server-study/assets/102507306/dbaeccd9-2039-4c80-8fa6-78b87b9306e0">


## 2\. 보안 그룹 생성하기

1.  생성한 `VPC`에 연결하여 들어오고 나갈 때 (Inbound & Outbound)의 규칙을 설정하기 위함이다.
2.  목차에서 `보안 그룹`을 선택하고, '생성하기'를 클릭한다.  
    <img width="260" alt="1" src="https://github.com/oxdjww/server-study/assets/102507306/b8ae0c22-faa3-4d55-89da-83023247e336">

3.  이 보안그룹을 아까 생성한 `umc-tete VPC`에 할당해준다.  
      <img width="886" alt="2" src="https://github.com/oxdjww/server-study/assets/102507306/e7d445d0-51aa-4b02-8fc5-9b42622967b1">

4.  인바운드 규칙을 다음과 같이 설정한다.  
    ![3](https://github.com/oxdjww/server-study/assets/102507306/6c8b7077-dc7f-4fd8-91e0-bb4a277a8d70)

```
3000 포트 : `nginx`를 위한 포트로 열어둔 것
8080 포트 : 기본적으로 80포트가 `HTTP`를 처리하지만, 추가적인 처리를 위해 자주 쓰이는 포트 번호가 8080이다.
```

## 3\. EC2 생성하기

1.  목차에서 `인스턴스`를 선택하고, '생성하기'를 클릭한다.  
    <img width="648" alt="1" src="https://github.com/oxdjww/server-study/assets/102507306/082718e7-f3cf-4d03-a973-d0298519ffe2">

2.  linux image로는 22.04 가 latest ver이지만, 트러블 슈팅을 편하게 하기 위해 20.04 ver으로 선택하였다.  
    <img width="813" alt="2" src="https://github.com/oxdjww/server-study/assets/102507306/f7bd2952-e38e-4382-9cd3-7ea48cb32ede">

3.  이름은 자유롭게 설정한다. 그리고 `EC2 인스턴스`에 접속하기 위해서는 공개키/개인키의 키 쌍이 필요한데, 이를 `RSA`와 `*.pem` 형식으로 생성해준다.  
    <img width="636" alt="3" src="https://github.com/oxdjww/server-study/assets/102507306/d0fdc23a-7a50-445d-a4aa-0bdfc587b03a">

4.  '편집' 버튼을 클릭하여 아까 만든 보안그룹을 할당해주고, 서브넷과 VPC 등을 아래와 같이 설정해준다.  
    <img width="808" alt="4" src="https://github.com/oxdjww/server-study/assets/102507306/4dad56a7-c75a-4b62-ac4e-a740ffc8bb69">

5.  볼륨은 프리티어 최대값으로 설정해주었다.  
    <img width="801" alt="5" src="https://github.com/oxdjww/server-study/assets/102507306/538e0790-c875-4df4-8434-d1ccec14b8b1">


## 4\. 탄력적 IP 설정하기

1.  목차에서 `탄력적 IP`를 선택한다.  
    <img width="265" alt="6" src="https://github.com/oxdjww/server-study/assets/102507306/77512582-cef7-4dd8-b82c-d1bc5ea9d87d">

2.  사진과 같이 `네트워크 경계 그룹` 및 기타 사항은 디폴트로 두고 완료한다.  
    <img width="915" alt="7" src="https://github.com/oxdjww/server-study/assets/102507306/411431fb-cfd5-4f45-a8c0-92c2a1832a3c">

3.  `탄력적 IP 주소 연결`을 선택한다.  
    <img width="915" alt="7" src="https://github.com/oxdjww/server-study/assets/102507306/3a65f083-5869-4a3a-abe7-ed1d314c02d1">

4.  아까 생성한 `EC2 인스턴스`를 연결해준다.  
    <img width="831" alt="8" src="https://github.com/oxdjww/server-study/assets/102507306/b3912b9b-2d11-406f-9aa4-a820770afe57">


## 5\. IntelliJ 원격접속

1.  IntelliJ에서, `Tools > Deployment > Browse Remote Host`을 선택한다. (Mac os 기준)  
    ![image](https://github.com/oxdjww/server-study/assets/102507306/0665a90e-2f4e-4165-9a0a-896bf589e4a8)


2.  그럼 화면 우측에 이런 창이 뜬다. 여기서, `...` 버튼을 클릭한다.  
    ![image](https://github.com/oxdjww/server-study/assets/102507306/302f152e-8cd8-4bb5-a890-2dbf81d2e6e1)


3.  그러면 IntelliJ와 연결할 서버를 추가할 수 있다. 이름을 지정해주자.  
    ![image](https://github.com/oxdjww/server-study/assets/102507306/a1dcd971-4987-4070-99aa-a43897b48309)


4.  이름을 지정하고 서버를 생성하는 창이다.  
    ![image](https://github.com/oxdjww/server-study/assets/102507306/52722d9b-58b3-4ad3-9650-b4a4664b671b)


5.  서버 설정을 위해, `SSH configuration` 우측 끝에 있는 `...` 버튼을 클릭하여 `SSH` 접속 관련 설정을 해줄 것이다.  
    ![image](https://github.com/oxdjww/server-study/assets/102507306/be5fa410-4a45-4ed9-88fa-d31af76bb4b9)


    a. SSH 접속 설정 화면이다.  
    ![image](https://github.com/oxdjww/server-study/assets/102507306/f2a53f2e-d50e-4ab0-9aab-9491d0672cc2)

    b. 우선 `Authentication type`을 다음과 같이 설정하여 `EC2` 생성 시 같이 만들어준 `*.pem`을 활용할 것이다.  
    ![image](https://github.com/oxdjww/server-study/assets/102507306/ab950bc0-abbf-4d48-878e-8cc66444c5cb)

    c. 나머지는 다음과 같이 입력하면 된다.
    
    ```
     `Host` : {EC2 Instance의 public IPv4}
     `Username` : ubuntu
     `Authentication type` : Key pair OpenSSH or PuTTY
     `Private key file` : {`*.pem` 파일의 경로}
    ```
    
    나머지는 기본 값으로 설정하고, `Test Connection`을 통해 연결이 성공했는지 확인한다.  
    ![image](https://github.com/oxdjww/server-study/assets/102507306/0f38462a-8c51-42a2-96ca-af126aeb40b3)
    ![image](https://github.com/oxdjww/server-study/assets/102507306/036a2d89-4c40-44b9-932e-a47ebab668ba)

    이러면 성공!
6.  `OK`를 누르고 나가면 이제 우측에 아까 연결한 서버가 뜨는 것을 확인할 수 있다.  
    ![image](https://github.com/oxdjww/server-study/assets/102507306/b7642f6f-241d-463f-a41a-3dc3ca44e82a)


## 6\. VSCode 원격접속

1.  `VSCode` 좌측 탭에서 `확장(Extension)`을 선택하고, 아래와 같이 검색 후 설치한다.  
    ![image](https://github.com/oxdjww/server-study/assets/102507306/61ffb616-e05b-482c-91a1-373e2f2c9d31)

2.  그리고 `f1`(`fn` + `f1`)를 눌러 `SSH Configuration File`을 띄운다.  
    ![image](https://github.com/oxdjww/server-study/assets/102507306/3d93e0e4-8287-426a-a6e4-b9ae7b124be1)
  
    ![image](https://github.com/oxdjww/server-study/assets/102507306/6d5c41a1-cec9-4ffb-ad63-b2586eb24051)

3.  해당 파일에서, 아래와 같은 형식으로 작성해준다.
    ![image](https://github.com/oxdjww/server-study/assets/102507306/bfd7f398-bb00-422b-9821-4f9f472a9c3c)

    눈치 챘겠지만, `VSCode`에서 SSH 접속 시, `SSH Configuration File`의 정보를 파싱하여 접속한다.
    ```
    Host : {이름 아무거나 상관없음}
      Hostname : {접속할 서버의 IPv4 주소}
      User : ubuntu
      IdentityFile : {`*.pem` 파일의 경로}
    ```
4.  이제 다시 `f1`(`fn` + `f1`)를 눌러 `호스트에 연결`을 선택하고, 아까 생성한 SSH 호스트에 접속한다.  
    ![image](https://github.com/oxdjww/server-study/assets/102507306/378b60ce-c5a9-4967-9c8f-bbae401131de)

    a. 이 때, 다음과 같은 오류를 만날 수 있다.  
    ![image](https://github.com/oxdjww/server-study/assets/102507306/330293e8-3034-41d8-977e-f80393c72142)

    b. key 파일(`tete.pem`)을 이용하여 접속을 시도할 때, key의 접근 권한이 너무 공개적이라 이를 제한한다는 의미이다.  
    ![image](https://github.com/oxdjww/server-study/assets/102507306/89d0509d-ad66-4632-b060-0b4309987ee4)

    c. 터미널에서 key file의 디렉토리로 이동하여 key의 접근 권한을 바꿔주고, 다시 시도하여 해결할 수 있었다.  
    ![image](https://github.com/oxdjww/server-study/assets/102507306/5afd0e86-a415-4e5e-a741-7320046342c3)

    [chmod란?](https://oxdjww.tistory.com/entry/Linux-Command-chmod)
5. 접속 성공  
    ![image](https://github.com/oxdjww/server-study/assets/102507306/393b96fe-a4d8-48cb-b417-3999aebd4cbe)


## 7\. NGINX test

1.  linux에 접속 성공한 터미널에서, 아래의 명령어를 `cmd+c,v` 해준다.
    
    ```
     sudo apt update
     sudo apt upgrade -y
     sudo apt install nginx -y
    ```
    
2.  그리고 Host os (혹은 아무데서나)의 브라우저에서 `EC2 Instance`의 IP주소로 접근 시 다음과 같은 **nginx welcome page**를 볼 수 있다!  
    ![image](https://github.com/oxdjww/server-study/assets/102507306/d9e82cd1-0678-4e75-936e-f61dcef69d92)


---

감사합니다.
