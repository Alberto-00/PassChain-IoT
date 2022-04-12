### PASSI OBBLIGATORI
- [ ] 1) comunicazione 'bluetooth' (mostrare il dispositivo per il pairing bluetooth) `Vedere link step successivi`

- [ ] 2) sicurezza comunicazione bluetooth [LINK](https://www.youtube.com/watch?v=TwexLJwdLEw&t=125s)

- [ ] 4) simulare una tastiera attraverso il bluetooth [LINK](https://www.youtube.com/watch?v=4sIkW7wogrE&t=8s)

- [ ] 4) inviare stringhe diverse attraverso il bluetooth(simulando una tastiera)
		[video 1](https://www.youtube.com/watch?v=EWKAyQBdcYM&t=152s)
		[video 2](https://www.youtube.com/watch?v=BkfmBk6OeQM&t=345s)

- [ ] 5) realizzare l'interfaccia(menu e funzioni tasti) sullo schermo [LINK](https://www.youtube.com/watch?v=u7277VShso4)

- [ ] 6) usare il sensore di impronte per l'autenticazione [LINK](https://www.youtube.com/watch?v=Y87V0O1yMCk&t=123s)

- [ ] 7) trovare un modo per proteggere i dati(criptare i dati), impedire di comunicare con la scheda senza una password, o comunque bloccarla in qualche modo
		[Flash ecription](https://www.youtube.com/watch?v=16jF0HUyedg)
		[Base64 encoding](https://www.youtube.com/watch?v=jm45imFsZTw)
		[KRACK Wifi protection](https://www.youtube.com/watch?v=Hkr60GE5yfY&t=90s)

- [ ] 8) gestire i timeout, il deep sleep e lo spegnimento(attraverso interruttore) della scheda [LINK](https://www.youtube.com/watch?v=y1R2y8dCsIg&t=305s)

- [ ] 9) capire come salvare le password sul dispositivo(attraverso cavo, bluetooth o wifi), e gestirne gli accessi e le informazioni [LINK](https://www.youtube.com/watch?v=2TDAAese2Gg)

- [ ] 10) collegare e gestire carica della batteria con percentuale sul display del dispositivo [LINK](https://www.youtube.com/watch?v=osAOdmZuvDc)

- [ ] 11) testare il funzionamento del prototipo

- [ ] 12) disegnare e stampare la custodia del dispositivo 

- [ ] 13) assemblare il tutto in modo definitivo e fare ulteriori testing


### EXTRA
- [ ] 1) aggiungere animazioni all'avvio del dispositivo [LINK](https://www.youtube.com/watch?v=Bl1C7Vdl3GA)

- [ ] 2) aggiungere animanzione(matrix) durante il salvataggio delle password sul dispositivo [LINK](https://www.youtube.com/watch?v=uexWyEWtVzg&t=203s)

- [ ] 3) aggiungere l'icona della batteria con il relativo stato [LINK](https://www.youtube.com/watch?v=osAOdmZuvDc)

extra... ancora da definire

### OPTIONAL 
- [ ] 1) Aggiunta di una sdCard con relativo modulo per incrementare la memoria [LINK](https://www.youtube.com/watch?v=e1xOgZsnAuw)

### COMPONENTI
+ Sensori di impronte aptici:
	+ [Opzione 1](https://it.aliexpress.com/item/1005003014492546.html?spm=a2g0o.productlist.0.0.15015ee6Fn3WmL&algo_pvid=c07cd617-7446-41c4-b66f-5b82ea80a22c&algo_exp_id=c07cd617-7446-41c4-b66f-5b82ea80a22c-10&pdp_ext_f=%7B%22sku_id%22%3A%2212000026983243135%22%7D&pdp_pi=-1%3B8.62%3B-1%3B-1%40salePrice%3BEUR%3Bsearch-mainSearch)
	+ [Opzione 2](https://it.aliexpress.com/item/1005003058467743.html?spm=a2g0o.search0304.0.0.373c2fca7Wc9Ie&algo_pvid=be494e38-46a8-43b3-997a-6386c1f4ee1c&algo_exp_id=be494e38-46a8-43b3-997a-6386c1f4ee1c-51)
	+ [Opzione 3](https://it.aliexpress.com/item/4000261423993.html?spm=a2g0o.search0304.0.0.373c2fcav5Pu2E&algo_pvid=52597cc6-0e8e-4a03-9040-4aa424c404ef&algo_exp_id=52597cc6-0e8e-4a03-9040-4aa424c404ef-33)

+ [TTGO ESP32](https://www.amazon.it/gp/product/B07VNG9D52/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)
+ [Batteria 500mah](https://www.amazon.it/gp/product/B082NZGW3V/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1)
+ [DIP Switch](https://www.amazon.it/Assortimento-Posizione-Montabile-Confezione-Circuiti/dp/B07CB8Z6ZP/ref=sr_1_7?crid=3MXFNVWQI9G0P&keywords=interruttori+dip&qid=1648557058&sprefix=interruttore+dip%2Caps%2C131&sr=8-7)


### DOCUMENTAZIONE
+ [TTGO ESP32](http://www.lilygo.cn/prod_view.aspx?TypeId=50033&Id=1126&FId=t3:50033:3)
+ Tempo stimato batteria 500mah usando solo 300mah per prezervare la salute della batteria **857 ore equivalgono a 35.708333 giorni**.
+ [Tizio con tanti progetti da cui prendere spunto](https://www.youtube.com/c/ThatProject/videos)
+ Se si hanno problemi con la compilazione del codice dopo che si ha già installato i driver per il computer e aver scaricato da arduino ide i driver per la scheda seguire questa guida [LINK](https://arduino-esp8266.readthedocs.io/en/latest/faq/a04-board-generic-is-unknown.html)
+ Rimappare [LINK](https://www.esp32.com/viewtopic.php?t=17546)  le porte hardware dell'ESP32 TTGO:
	+ Procedura [LINK](https://www.b4x.com/android/forum/threads/remap-hardware-serial-ports-on-esp32.123750/)
	+ Percorso su MacOS: /Users/NomeUtente/Documents/Arduino/hardware/espressif/esp32/cores/esp32/HardwareSerial.cpp 
+ Utilizzare il sensore fingerprint Adafruit con Python richiede la seguente procedura [LINK](https://docs.circuitpython.org/projects/fingerprint/en/latest/)
+ O Utilizzando MicroPython è richiesta la seguente libreria [LINK](https://docs.circuitpython.org/projects/fingerprint/en/latest/_modules/adafruit_fingerprint.html)
