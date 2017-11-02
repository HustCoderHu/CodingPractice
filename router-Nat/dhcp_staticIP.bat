@echo off
:configure

REM 是注释

REM info about router and its lan
REM gateway route into lan
REM for example: ping 192.168.166.110 from 115.156.166.110
set dest=192.168.0.0
set routerWanIP=115.156.156.128
REM arp -a |findstr "14-da-e9-e2-71-cd"

REM !!!!!!!!!!!!!! attention !!!!!!!!!!!!!!
REM adapterName & myIP need modified according to your windows
REM set adapterName=Ethernet
REM !!!!!!!!!!!!!! attention !!!!!!!!!!!!!!

REM ---- 115 ip
REM ----
REM set myIP=115.156.16.
REM set mask=255.255.254.0
REM set gateway=115.156.166.202


REM ---- 192 ip
REM ----
set myIP=192.168.x.x
set mask=255.255.0.0
set gateway=192.168.0.1


REM ---- DNS config
REM ----
set dnserver1=114.114.114.114
set dnserver2=8.8.8.8

if defined adapterName (
    goto deploy
) else (
    echo !!!!  edit this file before execute  !!!!
    pause
    goto end
)

REM ==== ==== ==== ====   ==== ==== ==== ====  ==== ====
REM ==== ==== ==== ====   ==== ==== ==== ====  ==== ====
:deploy
@echo off
cls
echo 1: ================  dhcp  ================
echo 2: ================ static ================
echo 3: ================ add route to lan ======
echo 4: ================ del route to lan ======
echo 5: ================  exit  ================
echo
REM choice /C 12345
set /p input=
REM @echo on
if %input% == 5 goto end
if %input% == 4 goto del_route
if %input% == 3 goto add_route
if %input% == 2 goto static
if %input% == 1 (
    goto dhcp
) else (
goto end
)

:dhcp
echo dhcp
netsh interface ip set address %adapterName% dhcp
REM netsh interface ip set dns Ethernet dhcp
pause
goto deploy

:static
echo static
netsh interface ip set address %adapterName% static %myIP% %mask% %gateway%
netsh interface ip add dns %adapterName% %dnserver1%
netsh interface ip add dns %adapterName% %dnserver2%
pause
goto deploy

:add_route
echo add_route
route -p delete %dest%
route -P add %dest% mask %mask% %routerWanIP%
pause
goto deploy

:del_route
echo del_route
route -p delete %dest%
pause
goto deploy

:end