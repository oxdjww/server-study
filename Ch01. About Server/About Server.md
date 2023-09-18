<div class="markdown-body">
<h2>Ch01. 서버란 무엇인가</h2>
<h3>Overview</h3>
<hr>
<p>client - server 간 데이터의 송수신 방식 및 과정 이해</p>
<h3>서버의 정의</h3>
<hr>
<p>client에 대한 응답을 주는 개체<br>즉,<br>서버란 OS에 의해 동작하는 프로세스이며, 클라이언트의 역할을 하는 프로세스와 소켓을 통해 IPC를 수행하는 개체</p>
<h3>Knowledge</h3>
<hr>
<h4>About System Call</h4>
<p>응용 프로그램의 요청에 따라 커널에 접근하기 위한 인터페이스이다.<br>이렇게 커널에 접근하여 운영체제의 커널이 제공하는 서비스를 이용하여 응용 프로그램의 요청을 수행한다.<br><a href="https://velog.io/@nnnyeong/OS-%EC%8B%9C%EC%8A%A4%ED%85%9C-%EC%BD%9C-System-Call">Ref</a></p>
<h4>About Process &amp; Thread</h4>
<p>Process : 운영체제로부터 자원을 할당받은 작업(task)의 단위<br>Thread : process가 할당받은 자원을 이용하는 실행 흐름의 단위<br><a href="https://velog.io/@aeong98/%EC%9A%B4%EC%98%81%EC%B2%B4%EC%A0%9COS-%ED%94%84%EB%A1%9C%EC%84%B8%EC%8A%A4%EC%99%80-%EC%8A%A4%EB%A0%88%EB%93%9C">Ref</a></p>
<h4>About TCP/IP Model</h4>
<p>L4 : Application Layer<br>L3 : Transport Layer<br>L2 : Internet Layer<br>L1 : Link(Network Interface) Layer<br><a href="https://ariz1623.tistory.com/327">Ref</a></p>
<h4>About TCP &amp; UDP</h4>
<p>TCP : Transmission Control Protocol<br>UDP : User Datagram Protocol<br><a href="https://velog.io/@hidaehyunlee/TCP-%EC%99%80-UDP-%EC%9D%98-%EC%B0%A8%EC%9D%B4">Ref</a></p>
<h3>IP Address &amp; Port Number</h3>
<hr>
<p>IP address : 네트워크 상에서 통신 시에, 자신을 식별할 수 있는 고유한 정보<br>IP address의 부족함을 해결하기 위한 기술</p>
<ul>
<li>NAT</li>
<li>서브네팅</li>
<li>IPv6  </li>
</ul>
<p>이 네트워크 상의 통신은 컴퓨터와 컴퓨터가 통신을 하는 것은 맞지만, 구체적으로는 컴퓨터 내의 한 process와 다른 컴퓨터 내의 process가 통신을 하는 것이다.<br>그러므로 통신을 할 때 process를 구분하기 위한 식별자가 필요한데, 이것이 바로 port number이다. <br>다음과 같은 형식을 사용한다.<br><code>[&quot;수신할 프로세스가 동작하고 있는 컴퓨터의 ip address&quot;:&quot;수신한 프로세스가 부여받은 port number&quot;]</code></p>
<h3>Data Transmission Process</h3>
<hr>
<h4>데이터를 어떻게 송신할까?</h4>
<p>일반적으로 TCP/IP 모델을 기준으로, user level에서 application끼리 데이터를 주고받는 상황을 가정할 것이다.<br>application layer에서 user data를 아래 계층인 transport layer로 보내고, 이 때 data가 encapsulate되고, application header가 붙으며 application data가 된다.<br>- <em>나중에 수신할 때 decapsulate되며 어느 process에 이 data가 할당되는지 파악할 수 있다.</em><br>transport layer에서는 application data가 encapsulate되고, tcp header가 붙으며 tcp segment(udp의 경우 datagram이라고도 함)가 된다.<br>- <em>나중에 수신할 때 decapsulate되며 packet이 어느 port number로 할당되어야 하는지 파악할 수 있다.</em><br>internet layer에서는 tcp segment가 encapsulate되고, ip header가 붙으며 ip packet이 된다.<br>- <em>나중에 수신할 때 decapsulate되며 ip header를 통해 어느 ip address로 routing될지 결정한다.</em><br>link layer에서는 ethernet header를 붙이며 ethernet 통신 간 패킷을 forward할 수 있는 식별자로 사용한다.<br>- <em>나중에 수신할 때 ethernet기반 통신에서 어느 host로 가야할지 알 수 있다.</em></p>
<h3>Socket</h3>
<hr>
<h4>TCP Socket</h4>
<p>연결 지향, 신뢰성 있는 데이터 송수신 담당</p>
<h4>UDP Socket</h4>
<p>비연결 지향</p>
<h4>Socket Programming Practice</h4>
<p><a href="https://github.com/oxdjww/server-study/tree/main/Ch01.%20About%20Server/src">socket_programming_github.io</a></p>
</div>