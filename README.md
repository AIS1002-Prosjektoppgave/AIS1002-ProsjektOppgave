AIS1002 Prosjektoppgave - 3D Sjakk

Dette er et program som gir muligheten til å spille sjakk mot noen andre på samme datamaskinen. Sjakkbrikkene og sjakkbrettet er fremstilt 3-dimensjonalt. For å visualiserer sjakkbrettet er det brukt et tredjepartsbibliotek kalt "threepp". 


Innholdsfortegnelse:


Innstallasjon:

For å kunne bruke programmet på din maskin må du ha følgende installert:

Vcpkg - Dette er et åpent kildekodeprosjekt fra Microsoft som er en pakkehåndterer for C++-avhengigheter. Dette forenkler prosessen med å finne, installere og administrere tredjepartsbiblioteker og avhengigheter i C++-prosjekter.

Threepp - Dette er et tredjepartsbibliotek som blir brukt for visualisering av sjakkbrikker og sjakkbrett. Den blir også brukt for å definere hva musknapper og taster har for en funksjon.

Assimp - Dette blir brukt for å laste .stl filer som objekt.


Bruk:

For å kunne programmet må du ha installert og konfigurert programmene ovenfor. Etter det er gjort kan du åpne prosjektet her å kjøre main.cpp filen. Det skal da poppe opp et vindu som vist under:
![Skjermbilde 2023-05-14 kl  17 30 05](https://github.com/AIS1002-Prosjektoppgave/AIS1002-ProsjektOppgave/assets/122883584/9613e134-5f4f-4d91-93a4-47d5d5e85dc0)


Ved å trykke inn mushjulet og holder inne, kan du dra musen slik at du for rotert perspektiven du ser sjakkbrettet ifra.
Du kan også zoome inn og ut ved å vri på mushjulet slik det passer deg.

For å flytte brikkene kan du høyretrykke på ruten (eller direkte på brikken) og så et nytt høyreklikk til der du ønsker å flytte denne. Merk, at feltet som brikken skal flyttes til må være ledig. Se bildet under:
![Skjermbilde 2023-05-14 kl  17 32 28](https://github.com/AIS1002-Prosjektoppgave/AIS1002-ProsjektOppgave/assets/122883584/ccdcd3a8-811d-4cf1-93f7-bfdf1f0c978e)

NB! Grunnet mangel på tid, rakk vi ikke å fullføre programmet slik vi hadde tenkt. Vi har begynnt på en header som skal implementere reglene for hvordan sjakkbrikkene skal oppføre seg og at de kan slå ut andre sjakkbrikker. Men dette rakk vi altså ikke å fullføre. 


Dokumentasjon:

Vcpkg - https://github.com/microsoft/vcpkg#documentation
Threepp - https://github.com/AIS1002-OOP-V23/threepp
Assimp - https://github.com/assimp/assimp


Feilsøking:

Dersom en skal feilsøke programmet er det blant annet lagt til en tekst i konsollen når programmet kjører som viser hva raycasten (funksjonen som er brukt for å ta tak i brikker) treffer.

Det er også laget egne tester som skal teste at programmet kjører slik det skal. Desse ligger i mappen "tests" og der kan du kjøre de forskjllige testen i tests.cpp for å teste at funksjoner som for eksempel: skaleringen på sjakkbrikkene er rett, at kalkuleringen av at brikken automatisk plasseres på midten av ruten er rett.



Vi har tatt utganspunkt i å lage 3D-sjakk i mappeinnleveringen vår. Vi har lagt ned en god andel timer så langt, og kommet greit igang. Vi har fått til en baseline der vi har hentet sjakkbrikker ved .stl filer og plassert disse på sjakkbrettet, samt lager ferdig utseende og det visuelle i forhold til sjakkspillet. Neste steg nå blir å implementere flytting av brikker, samt få lagt inn regler i sjakkspillet slik at det faktisk går ann å spille noe som helst. Det er mye jobb som gjenstår, men føler vi har kommet greit igang.

Når det kommer til selve kodingen har det blitt mye frem og tilbake, med prøving av forskjellige funksjoner der vi har måttet se ann hva som fungerer best. vi har også tatt utgagnspunkt i eksmepelkodene til threepp for å se hvordan koden eventuelt kan bygges opp. Sammen med dette har vi også brukt ressurser fra internett som god inspirasjon i koden, spesielt der vi har stått litt fast og kommet videre.

Det er brukt forskjellige headers for å få til en mer oversiktlig kode
