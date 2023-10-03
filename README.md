# CorretorDeColuna
Projeto para um corretor de coluna usando giroscópios e acelerômetros.
A inteção é usar dispositivos MPU-6050 para verificar inclinações em pontos estratégicos do corpo do usuário.
Processando esses dados com um ESP32 espera-se alertar o usuário acerca de uma má postura, a ideia inicial é
utilizar pequenos motores vibratórios para isso.

Os pontos fundamentais do projeto sâo:
- Wearable, o que implica em ser confortável de usar por longos períodos de tempo;
- Portátil;
- Ciclos de carga da bateria que permitam o uso contínuo por pelo menos 24h;
- Necessita de validação especializada por profissionais da área (fisioterapia, terapia ocupacional, ortopedia e educação física).

