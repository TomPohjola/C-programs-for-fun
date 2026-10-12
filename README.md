# C-programs-for-fun
Repositorio omille C-kielisille pienille ohjelmille, mitä olen tehnyt huvikseni.

PointerArithmetics_Threads_and_Binarysearching kansio sisältää ohjelman, minkä tarkoitus on lähinnä demonstroida osoittimien käyttämistä C-kielessä ja miten prosessi voi luoda useita säikeitä ja miten niitä hallitaan.

  1. aliohjelma on harjoitus osoitinaritmetiikasta, missä taulukon elementtejä käydään läpi lisäämällä ensimmäisen elementin muistiosoitteeseen sizeof(int) * käyttäjän antama luku ja printtaamalla muistiosoite.

  2. aliohjelma on yksinkertainen liukulukujen summausfunktio, missä parametrit ovat osoittimia muuttujiin --> vältettään muuttujien kopionti ja hyödynnetään C:n osoittimia.

  3. aliohjelma luo miljoonan alkion järjestetyn taulukon, minne laitetaan satunnaisia lukuja, mutta edellisiä suurempia lukuja. Sitten luodaan neljä säiettä, joista jokainen tekee binäärihaun tietyllä indeksialueella
     (esim indeksit 0-250,000) ja ilmoittaa, mikäli etsitty luku löytyy. Tämän jälkeen muut säikeet lopettavat etsinnän ja säikeiden luonti keskeytetään, mikäli niitä on vielä luomatta. Ohjelman idea on demonstroida moni-
     säikeistä prosessia, kriittisen alueen hallintaa ja tietorakenteiden soveltamista oikeaan tarkoitukseen.
