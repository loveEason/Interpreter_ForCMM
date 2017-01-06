Lexical result is as follow:
   1: int a,b[10];
       1:Key word: int
       1:Identifier:  a
       1:Limitor: ,
       1:Identifier:  b
       1:Limitor: [
       1:Int value:  10
       1:Limitor: ]
       1:Limitor: ;
   2: real c[10];
       2:Key word: real
       2:Identifier:  c
       2:Limitor: [
       2:Int value:  10
       2:Limitor: ]
       2:Limitor: ;
   3: read(a);
       3:Key word: read
       3:Limitor: (
       3:Identifier:  a
       3:Limitor: )
       3:Limitor: ;
   4: if(a<=10) {
       4:Key word: if
       4:Limitor: (
       4:Identifier:  a
       4:Operator: <=
       4:Int value:  10
       4:Limitor: )
       4:Limitor: {
   5:    for(int i=0;i<a;i=i+1) {
       5:Key word: for
       5:Limitor: (
       5:Key word: int
       5:Identifier:  i
       5:Operator: =
       5:Int value:  0
       5:Limitor: ;
       5:Identifier:  i
       5:Operator: <
       5:Identifier:  a
       5:Limitor: ;
       5:Identifier:  i
       5:Operator: =
       5:Identifier:  i
       5:Operator: +
       5:Int value:  1
       5:Limitor: )
       5:Limitor: {
   6:        b[i] = i;
       6:Identifier:  b
       6:Limitor: [
       6:Identifier:  i
       6:Limitor: ]
       6:Operator: =
       6:Identifier:  i
       6:Limitor: ;
   7:        c[i] = i/2;
       7:Identifier:  c
       7:Limitor: [
       7:Identifier:  i
       7:Limitor: ]
       7:Operator: =
       7:Identifier:  i
       7:Operator: /
       7:Int value:  2
       7:Limitor: ;
   8:    }
       8:Limitor: }
   9:    for(int i=0;i<a;i=i+1) {
       9:Key word: for
       9:Limitor: (
       9:Key word: int
       9:Identifier:  i
       9:Operator: =
       9:Int value:  0
       9:Limitor: ;
       9:Identifier:  i
       9:Operator: <
       9:Identifier:  a
       9:Limitor: ;
       9:Identifier:  i
       9:Operator: =
       9:Identifier:  i
       9:Operator: +
       9:Int value:  1
       9:Limitor: )
       9:Limitor: {
  10:        write(b[i]);
      10:Key word: write
      10:Limitor: (
      10:Identifier:  b
      10:Limitor: [
      10:Identifier:  i
      10:Limitor: ]
      10:Limitor: )
      10:Limitor: ;
  11:        write(c[i]);
      11:Key word: write
      11:Limitor: (
      11:Identifier:  c
      11:Limitor: [
      11:Identifier:  i
      11:Limitor: ]
      11:Limitor: )
      11:Limitor: ;
  12:    }
      12:Limitor: }
  13: }else {
      13:Limitor: }
      13:Key word: else
      13:Limitor: {
  14:    write(0);
      14:Key word: write
      14:Limitor: (
      14:Int value:  0
      14:Limitor: )
      14:Limitor: ;
  15: }
      15:Limitor: }
  16: 
  17: while(a>0) {
      17:Key word: while
      17:Limitor: (
      17:Identifier:  a
      17:Operator: >
      17:Int value:  0
      17:Limitor: )
      17:Limitor: {
  18:    a = a-1;
      18:Identifier:  a
      18:Operator: =
      18:Identifier:  a
      18:Operator: -
      18:Int value:  1
      18:Limitor: ;
  19: }
      19:Limitor: }
  20: 
  21: write(a);
      21:Key word: write
      21:Limitor: (
      21:Identifier:  a
      21:Limitor: )
      21:Limitor: ;
