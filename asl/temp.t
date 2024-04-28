function x2
  params
    _result integer array
    a integer array
  endparams

  vars
    i integer
    n integer
  endvars

     %1 = 0
     n = %1
     %2 = 0
     i = %2
  label startwhile1 :
     %3 = 10
     %4 = i < %3
     ifFalse %4 goto endwhile1
     %6 = a
     %5 = %6[i]
     %7 = 80
     %8 = %5 < %7
     ifFalse %8 goto endif1
     %9 = 1
     %10 = n + %9
     n = %10
  label endif1 :
     %11 = a
     %13 = a
     %12 = %13[i]
     %14 = 2
     %15 = %12 * %14
     %11[i] = %15
     %17 = a
     %16 = %17[i]
     writei %16
     writes "\n"
     %18 = 1
     %19 = i + %18
     i = %19
     goto startwhile1
  label endwhile1 :
     _result = n
     return
     return
endfunction

function main
  vars
    x integer 10
    i integer
    z integer
  endvars

     %1 = 0
     i = %1
  label startwhile1 :
     %2 = 10
     %3 = i < %2
     ifFalse %3 goto endwhile1
     %4 = 77
     %5 = %4 + i
     x[i] = %5
     %6 = 1
     %7 = i + %6
     i = %7
     goto startwhile1
  label endwhile1 :
     %8 = 0
     i = %8
  label startwhile2 :
     %9 = 10
     %10 = i < %9
     ifFalse %10 goto endwhile2
     %11 = x[i]
     writei %11
     writes "\n"
     %12 = 1
     %13 = i + %12
     i = %13
     goto startwhile2
  label endwhile2 :
     pushparam 
     pushparam x
     call x2
     popparam 
     popparam %14
     z = %14
     writes "z:"
     writei z
     writes "\n"
     %15 = 0
     i = %15
  label startwhile3 :
     %16 = 10
     %17 = i < %16
     ifFalse %17 goto endwhile3
     writes "x["
     writei i
     writes "]="
     %18 = x[i]
     writei %18
     writes "\n"
     %19 = 1
     %20 = i + %19
     i = %20
     goto startwhile3
  label endwhile3 :
     return
endfunction


