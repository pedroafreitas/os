/*
-------------->>> Simulando um Monitor <<<--------------
Para simular um monitor precisamos levar em consideração três questões principais:

1. Como garantir que as váriaveis locais não serão acessadas por outros procedimentos fora do monitor?
2. COmo garantir que o usuário pode apenas acessar a interface sem conhecer os detalhes do monitor?
3. Como consturir os limites do monitor para que MUTEX possa acontecer?

Para solucionarmos esses problemas vamos utilizar dois arquivos: um header para guardar os protótipos do monitor
e um arquivo de implementação. Ao implementar o monitor é preciso declarar suas variáveis como static. Também 
precisaremos usar o lock do muter para limitá-lo.

Nosso monitor vai manter um contador, cujo valor pode ser incrementado ou decrementado e até mesmo resetado. Teremos
uma função para inicialização e de recuperação do valor do contador- getMonitor().

No arquivo monitor.h encontram-se os protótipos dessas funções.

No arquivo monitor.c encontram-se as funções do monitor e suas variáveis internas.
-------------->>> Simulando um Monitor <<<--------------
*/