# AIS1002 Prosjektoppgave - 3D Sjakk

Dette er tenkt å bli et program som gir muligheten til å spille sjakk mot noen andre på samme datamaskinen.Men grunnet mengel på tid rakk vi dessverre ikke å fullføre dette. Det har gått mye tid på feilsøking. Sjakkbrikkene og sjakkbrettet er fremstilt 3-dimensjonalt. For å visualiserer sjakkbrettet er det brukt et tredjepartsbibliotek kalt "threepp". 


## Innholdsfortegnelse:

1. Installsjon
2. Bruk av programmet
3. Dokumentasjon
4. Feilsøking
5. Lisens
6. Skapere
7. Kilder
8. Endringslogg


## Innstallasjon:

For å kunne bruke programmet på din maskin må du ha følgende installert:

1. Vcpkg - Dette er et åpent kildekodeprosjekt fra Microsoft som er en pakkehåndterer for C++-avhengigheter. Dette forenkler prosessen med å finne, installere og administrere tredjepartsbiblioteker og avhengigheter i C++-prosjekter.

2. Threepp - Dette er et tredjepartsbibliotek som blir brukt for visualisering av sjakkbrikker og sjakkbrett. Den blir også brukt for å definere hva musknapper og taster har for en funksjon.

3. Assimp - Dette blir brukt for å laste .stl filer som objekt.


## Bruk:

For å kunne programmet må du ha installert og konfigurert programmene ovenfor. Etter det er gjort kan du åpne prosjektet her å kjøre main.cpp filen. Det skal da poppe opp et vindu som vist under:
![Skjermbilde 2023-05-14 kl  17 30 05](https://github.com/AIS1002-Prosjektoppgave/AIS1002-ProsjektOppgave/assets/122883584/9613e134-5f4f-4d91-93a4-47d5d5e85dc0)


Ved å trykke inn mushjulet og holder inne, kan du dra musen slik at du for rotert perspektiven du ser sjakkbrettet ifra.
Du kan også zoome inn og ut ved å vri på mushjulet slik det passer deg.

For å flytte brikkene kan du høyretrykke på ruten (eller direkte på brikken) og så et nytt høyreklikk til der du ønsker å flytte denne. Merk, at feltet som brikken skal flyttes til må være ledig. Se bildet under:
![Skjermbilde 2023-05-14 kl  17 32 28](https://github.com/AIS1002-Prosjektoppgave/AIS1002-ProsjektOppgave/assets/122883584/ccdcd3a8-811d-4cf1-93f7-bfdf1f0c978e)

NB! Grunnet mangel på tid, rakk vi ikke å fullføre programmet slik vi hadde tenkt. Vi har begynnt på en header som skal implementere reglene for hvordan sjakkbrikkene skal oppføre seg og at de kan slå ut andre sjakkbrikker. Men dette rakk vi altså ikke å fullføre. 


## Dokumentasjon:

1. Vcpkg - https://github.com/microsoft/vcpkg#documentation

2. Threepp - https://github.com/AIS1002-OOP-V23/threepp

3. Assimp - https://github.com/assimp/assimp


## Feilsøking:

Dersom en skal feilsøke programmet er det blant annet lagt til en tekst i konsollen når programmet kjører som viser hva raycasten (funksjonen som er brukt for å ta tak i brikker) treffer.

Det er også laget egne tester som skal teste at programmet kjører slik det skal. Desse ligger i mappen "tests" og der kan du kjøre de forskjllige testen i tests.cpp for å teste at funksjoner som for eksempel: skaleringen på sjakkbrikkene er rett, at kalkuleringen av at brikken automatisk plasseres på midten av ruten er rett. Vi har valgt bruke Catch2 som test ramme.


## Lisens

Programmet krever ingen lisenser og kan brukes fritt frem av alle :)


## Skapere

*************************
Kandidat nummer: 10030
*************************
Kandidat nummer 10033
*************************

## Kilder

ChatGPT for å få nærmere forklaring og eksempelkoder på ting vi lurte på. Denne har også vert til god hjelp ved feilsøking av diverse ting.

StackOverflow for å hente inspirasjon når vi har stått litt fast. Og med tanke på struktureringen av koden.


## Endringslogg

Merk at det jevnlig har blitt jobbet med koden. Slik at datoene er et notat på når endringene som vi gjorde i perioden mellom versjonene var såpass intuitivet at det gidde en nyere opplevelse av koden

### Versjon 1.1.0 (2023-02-27)
Lagt til visning av sjakkbrett.
Lagt til grafisk fremstilling av sjakkbrikker.
Lagt til header for implementering av muskontroller.

### Versjon 1.1.1 (2023-03-28)
Implementert rotering og zoom.
Lagt til rett posisjonering av brikker.
Lagt til tester.
Lagt til implemntering av muskontroller.

### Versjon 1.1.2 (2023-04-15)
Fullstendig omskrevet kodebase for bedre struktur og ytelse.
Løst kjente problemer relatert til bruk av muskontroller.
Lagt assimp som dependency.

### Versjon 2.0.0 (2023-05-14)
Lagt til kommentarer.
Lagt til bedre struktur blant headers.
Lagt til flere tester.
Oppdatert README.

