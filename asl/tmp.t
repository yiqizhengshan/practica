function fact
  params
    _result integer array
    n integer array
  endparams

  vars
    f integer
  endvars

     %1 = 1
     f = %1
  label startwhile1 :
     %2 = 1
     %3 = n <= %2
     %3 = not %3
     ifFalse %3 goto endwhile1
     %4 = f * n
     f = %4
     %5 = 1
     %6 = n - %5
     n = %6
     goto startwhile1
  label endwhile1 :
     _result = f
     return
     return
endfunction

function main
  vars
    max integer
    i integer
    f integer
    end boolean
  endvars

     %1 = 0
     i = %1
     %2 = 1
     end = %2
     readi max
     %3 = i <= max
     ifFalse %3 goto endif1
     %4 = 0
     end = %4
  label endif1 :
  label startwhile1 :
     %5 = not end
     ifFalse %5 goto endwhile1
     writei i
     writes "!="
     pushparam 
     pushparam i
     call fact
     popparam 
     popparam %6
     writei %6
     writes "\n"
     %7 = i == max
     ifFalse %7 goto endif2
     %8 = 1
     end = %8
  label endif2 :
     goto startwhile1
  label endwhile1 :
     return
endfunction


