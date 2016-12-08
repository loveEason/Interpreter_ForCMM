Lexical result is as follow：
   1:     int i=5;
       1:Key word: int
       1:Identifier:  i
       1:Operator: =
       1:Int value:  5
       1:Limitor: ;
   2:     int sum=0;  //这是单行注释
       2:Key word: int
       2:Identifier:  sum
       2:Operator: =
       2:Int value:  0
       2:Limitor: ;
   3:     if(i>0) {
       3:Key word: if
       3:Limitor: (
       3:Identifier:  i
       3:Operator: >
       3:Int value:  0
       3:Limitor: )
       3:Limitor: {
   4:         sum+=i;
       4:Identifier:  sum
       4:Operator: +=
       4:Identifier:  i
       4:Limitor: ;
   5:         i--;
       5:Identifier:  i
       5:Operator: --
       5:Limitor: ;
   6:     }
       6:Limitor: }
   7:     real j=100.5;
       7:Key word: real
       7:Identifier:  j
       7:Operator: =
       7:Real value:  100.5
       7:Limitor: ;
   8: //    real k=50d;   //这会出错
   9:     /*
  10:     这是多行
  11:     注释
  12:     */
  13:     int array[] = {1,2,3,4};
      13:Key word: int
      13:Identifier:  array
      13:Limitor: [
      13:Limitor: ]
      13:Operator: =
      13:Limitor: {
      13:Int value:  1
      13:Limitor: ,
      13:Int value:  2
      13:Limitor: ,
      13:Int value:  3
      13:Limitor: ,
      13:Int value:  4
      13:Limitor: }
      13:Limitor: ;
  14:     for(int i=0;i<10;i++) {
      14:Key word: for
      14:Limitor: (
      14:Key word: int
      14:Identifier:  i
      14:Operator: =
      14:Int value:  0
      14:Limitor: ;
      14:Identifier:  i
      14:Operator: <
      14:Int value:  10
      14:Limitor: ;
      14:Identifier:  i
      14:Operator: ++
      14:Limitor: )
      14:Limitor: {
  15:         j += i;
      15:Identifier:  j
      15:Operator: +=
      15:Identifier:  i
      15:Limitor: ;
  16:     }
      16:Limitor: }
  17:     while(j>0) {
      17:Key word: while
      17:Limitor: (
      17:Identifier:  j
      17:Operator: >
      17:Int value:  0
      17:Limitor: )
      17:Limitor: {
  18:         j--;
      18:Identifier:  j
      18:Operator: --
      18:Limitor: ;
  19:     }
      19:Limitor: }
