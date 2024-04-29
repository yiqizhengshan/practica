function one
  params
    _result float
  endparams

   %1 = 1.0
   %2 = %1
   _result = %2
   return
   return
endfunction

function sort
  params
    v float array
  endparams

  vars
    i integer
    j integer
    jmin integer
    aux float
  endvars

     %1 = 0
     i = %1
  label startwhile2 :
     %2 = 20
     %3 = 1
     %4 = %2 - %3
     %5 = i < %4
     ifFalse %5 goto endwhile2
     jmin = i
     %6 = 1
     %7 = i + %6
     j = %7
  label startwhile1 :
     %8 = 20
     %9 = j < %8
     ifFalse %9 goto endwhile1
     %11 = v
     %10 = %11[j]
     %13 = v
     %12 = %13[jmin]
     %14 = %10 <. %12
     ifFalse %14 goto endif1
     jmin = j
  label endif1 :
     %15 = 1
     %16 = j + %15
     j = %16
     goto startwhile1
  label endwhile1 :
     %17 = jmin == i
     %17 = not %17
     ifFalse %17 goto endif2
     %19 = v
     %18 = %19[i]
     aux = %18
     %20 = v
     %22 = v
     %21 = %22[jmin]
     %20[i] = %21
     %23 = v
     %23[jmin] = aux
  label endif2 :
     %24 = 1
     %25 = i + %24
     i = %25
     goto startwhile2
  label endwhile2 :
     return
endfunction

function evenPositivesAndSort
  params
    v float array
  endparams

  vars
    i integer
  endvars

     %1 = 0
     i = %1
  label startwhile1 :
     %2 = 20
     %3 = i < %2
     ifFalse %3 goto endwhile1
     %5 = v
     %4 = %5[i]
     %6 = 0
     %8 = float %6
     %7 = %4 <=. %8
     %7 = not %7
     ifFalse %7 goto endif1
     %9 = v
     pushparam 
     call one
     popparam %10
     %9[i] = %10
  label endif1 :
     %11 = 1
     %12 = i + %11
     i = %12
     goto startwhile1
  label endwhile1 :
     %13 = v
     pushparam %13
     call sort
     popparam 
     return
endfunction

function main
  vars
    af float 20
    i integer
  endvars

     %1 = 0
     i = %1
  label startwhile1 :
     %2 = 20
     %3 = i < %2
     ifFalse %3 goto endwhile1
     readf %4
     af[i] = %4
     %5 = 1
     %6 = i + %5
     i = %6
     goto startwhile1
  label endwhile1 :
     %7 = &af
     pushparam %7
     call evenPositivesAndSort
     popparam 
     %8 = 0
     i = %8
  label startwhile2 :
     %9 = 20
     %10 = i < %9
     ifFalse %10 goto endwhile2
     %11 = af[i]
     pushparam 
     call one
     popparam %12
     %13 = %11 ==. %12
     %13 = not %13
     ifFalse %13 goto else1
     %14 = af[i]
     writef %14
     %15 = ' '
     writec %15
     %16 = 1
     %17 = i + %16
     i = %17
     goto endif1
  label else1 :
     %18 = '\n'
     writec %18
     return
  label endif1 :
     goto startwhile2
  label endwhile2 :
     %19 = '\n'
     writec %19
     return
endfunction


