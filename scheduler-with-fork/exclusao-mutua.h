/**
*
* UNIVERSIDADE DO ESTADO DO AMAZONAS
* Adriano Freitas - adrianofreitas.me
*
*/



//Exclusão	Mútua	com	espera	ocupada
void alternanciaEstrita(){
  while (TRUE) {
    while (turn != 0);
    critical_region());
    turn 1;
    noncritical_region();
  }

  while (TRUE) {
    while (turn != 1);
    critical_region());
    turn 0;
    noncritical_region();
  }
}
