#!/usr/bin/perl
 
use warnings;
use strict ;


sub type
{
  #print"hi\n";
  foreach my $value(@_)
  {   #print"value $value \n";
      if($value eq'+'||$value eq '*'||$value eq'!')
     {   
        return 1;#operators
     }
     elsif($value eq ')')
    {   
        return 2;#)
    }
     elsif($value ne '(')
    {   
        
        return 3;#operands
    }
  }
}
my $lenop=0;
my $lenor=0;
my @nmos;
my @pmos;
my @nconn;#series ,parallel,negation of nmos
my @assign;#helps in naming
my @operand;
my @operand1;
my @operator;
my @operator1;
my @infix=qw{ ( ! ( (  a * b ) * ( c + f ) ) )} ;#{( ! ( ( ( ! a ) * c ) + ( d * c ) ) )};#qw{( ! ( ( a + b ) * c ) )};#split(/\s+/,$ARGV[0])
my @charvalue =qw{ ( ! ( ( 0 * 1 ) * ( 0 + 1 ) ) ) };

my @match;
#for(my $p=0;$p<2;$p++)
#{
#  for(my $q=0;$q<4;$q++)
#   { 
#      $match[$p][$q]=split(/\s+/,$ARGV[$p][$q]);
#   }
#}
$match[0][0]='a';
$match[0][1]='b';
$match[0][2]='c';
$match[0][3]='f';
$match[1][0]=0;
$match[1][1]=1;
$match[1][2]=0;
$match[1][3]=1;

print"@infix\n@charvalue\n";
#print"$charvalue[0],$infix[2],$charvalue[4]\n";
my $t=0;
foreach my $value(@infix)
{
   
   #print"$value in\n";
   my $char = type($value);
   #print"return $char\n";
   if($char eq 1)    #operator
   {
     #print"$value\n";
     push( @operator,$value);
     push( @operator1,$charvalue[$t]);
     print"operator is @operator1\n";
     
      $lenop = $lenop + 1;
   }
   elsif($char eq 3) #operand
   {
     #print"$value\n";
     push( @operand,$value);
     push( @operand1,$charvalue[$t]);
     print"operand is @operand1\n";
     $lenor = $lenor + 1;
   }
 
   elsif($char eq 2)   #right bracket
   {
      
      my $outop=pop(@operator);
      my $out = pop(@operator1);
      #print"pop $outop \n";
      if($outop eq '!')
      { 
        push(@nconn,'n');
        my $out1=pop(@operand);
        push(@operand,$outop.$out1);
        push(@assign,$out1);
        push(@assign,$outop.$out1);
        #print"$outop.$out1";
        my $val=pop(@operand1);
        if($val eq 1)
        {
            $val=0;
        }
        else
        {
            $val=1;
        }
        push(@operand1,$val);
        print"value is @operand1\n";
      }     
      elsif($outop eq '+')
      {
        push(@nconn,'p');
        my $out1=pop(@operand);
        my $out2=pop(@operand);
        push( @operand , $out2.$outop.$out1);
        push(@assign,$out2);
        push(@assign,$out1);
        push(@assign,$out2.$outop.$out1);
        #print" $out2 $outop $out1 \n";
        my $val1=pop(@operand1);
        my $val2=pop(@operand1);
        my $val=$val1|$val2;
        print" $val2 $out $val1 = $val\n";
        push(@operand1,$val);
        print"value is @operand1\n";
      }
      elsif($outop eq '*')
      {
        push(@nconn,'s');
        my $out1=pop(@operand);
        my $out2=pop(@operand);
        push( @operand , $out2.$outop.$out1);
        push(@assign,$out2);
        push(@assign,$out1);
        push(@assign,$out2.$outop.$out1);
        #print" $out2 $outop $out1 \n";
        my $val1=pop(@operand1);
        my $val2=pop(@operand1);
        my $val=$val1&$val2;
        print" $val2 $out $val1 = $val\n";
        push(@operand1,$val);
    
        print"value is @operand1\n";
      }
      #print" operand @operand\n";

   }
   
    $t=$t+1;   
}
print"\n\nnconn @nconn\n@assign\n\n";
#
my $j=0;
my $k=0;
my $op=1;
my $len=scalar(@nconn);
my $i;
for($i=0;$i<$len;$i=$i+1)
{
  # print"$value 3$nconn[$i]\n";
   
   if($nconn[$i] eq 'p')
   {   
       #print"$value $nconn[$i]\n";
       my $valop1=length( $assign[$j] );
       
       my $valop2=length( $assign[$j+1] );
       my $valop3=length( $assign[$j+2] );
      # print"$valop1 ,$valop2,$valop3\n";
       if($valop1 eq '1' && $valop2 eq '1')   
       {
          
          #nmos part
          $nmos[$k][1]=$pmos[$k][1]=$assign[$j];
          $nmos[$k+1][1]=$pmos[$k+1][1]=$assign[$j+1];
          if($i eq 0)
          {
             
             $nmos[$k][0]=$nmos[$k+1][0]=$assign[$j+2];
             $nmos[$k][2]=$nmos[$k+1][2]='G';
             $pmos[$k][0]='vdd';
             $pmos[$k][2]=$pmos[$k+1][0]='c'.$op;
             $op=$op+1;
             $pmos[$k+1][2]=$assign[$j+2];
          }
          else#(($assign[$j] eq $assign[$j-1])||($assign[$j+1] eq $assign[$j-1]))
          {
            $nmos[$k][0]=$nmos[$k+1][0]=$assign[$j+2];
            $nmos[$k][2]=$nmos[$k+1][2]=$nmos[$k-1][0];
            $pmos[$k][0]=$pmos[$k-1][2];
            $pmos[$k][2]=$pmos[$k+1][0]='c'.$op;
            $op=$op+1;
            $pmos[$k+1][2]=$assign[$j].'+'.$assign[$j+1];        
          }
          #$nmos[$k][3]=$k;
          
          $k=$k+2;
       }
       elsif(($valop1 ne '1' && $valop2 eq '1')||($valop1 eq '1' && $valop2 ne '1'))
       {
           
         if($valop1 eq '1')
         {
           $nmos[$k][1]=$pmos[$k][1]=$assign[$j];
         }
         elsif($valop2 eq '1')
         {
           $nmos[$k][1]=$pmos[$k][1]=$assign[$j+1];
         }
           
           $nmos[$k][0]=$nmos[$k-1][0]=$assign[$j+2];
           $nmos[$k][2]=$nmos[$k-2][2];
           $pmos[$k][2]=$assign[$j+2];
           $pmos[$k][0]=$pmos[$k-1][2];
           
         $k=$k+1;
       }
       elsif($valop1 ne '1' && $valop2 ne '1')
       {
           if(($assign[$j] eq $assign[$j-1])||($assign[$j+1] eq $assign[$j-1]))
          {
             $nmos[$k-2][2]=$nmos[$k-4][2];
             $nmos[$k-1][0]=$nmos[$k-3][0]=$assign[$j+2];
             if($nconn[$i-1] eq 'p')
             {
                $nmos[$k-2][0]=$nmos[$k-1][0];
                $nmos[$k-1][2]=$nmos[$k-2][2];

             }
             $pmos[$k-1][2]=$assign[$j+2];
             if($nconn[$i-1] eq 's')
             {
                $pmos[$k-2][2]=$assign[$j+2];
              }
          }
       } 
       
       $j=$j+3;     
   }
   elsif($nconn[$i] eq 's')
   {
      if(length($assign[$j]) eq '1' && length($assign[$j+1]) eq '1')
      {
          
          $nmos[$k][1]=$pmos[$k][1]=$assign[$j];
          $nmos[$k+1][1]=$pmos[$k+1][1]=$assign[$j+1];
          if($i eq 0)
          { 
             
             $nmos[$k][2]='G';
             $nmos[$k][0]=$nmos[$k+1][2]='c'.$op;
             $op=$op+1;
             $nmos[$k+1][0]=$assign[$j+2];
             $pmos[$k][0]=$pmos[$k+1][0]='vdd';
             $pmos[$k][2]=$pmos[$k+1][2]=$assign[$j+2]#$assign[$j].'*'.$assign[$j+1];

          }
          else
          {
            
             $nmos[$k][0]=$nmos[$k+1][2]='c'.$op;
             $op=$op+1;
             $nmos[$k][2]=$nmos[$k-1][0];
             $nmos[$k+1][0]=$assign[$j+2];
             $pmos[$k][0]=$pmos[$k+1][0]=$pmos[$k-2][2];
             $pmos[$k][2]=$pmos[$k+1][2]=$assign[$j+2];
          }
           $k=$k+2;
       }
      elsif((length($assign[$j]) ne '1' && length($assign[$j+1]) eq '1')||(length($assign[$j]) eq '1' && length($assign[$j+1 ]) ne '1'))
       {
          if(length($assign[$j]) eq '1')
          {
            $nmos[$k][1]=$pmos[$k][1]=$assign[$j];
          }
          elsif(length($assign[$j+1]) eq '1')
          {
            $nmos[$k][1]=$pmos[$k][1]=$assign[$j+1];
          }
          $nmos[$k][0]=$assign[$j+2];
          $nmos[$k][2]=$nmos[$k-1][0];
          $pmos[$k][2]=$pmos[$k-1][2]=$assign[$j+2];
          $pmos[$k][0]=$pmos[$k-2][0];
         $k=$k+1;
       }
       elsif(length($assign[$j]) ne '1' && length($assign[$j+1]) ne '1')
       {
          if(($assign[$j] eq $assign[$j-1])||($assign[$j+1] eq $assign[$j-1]))
          {
             $nmos[$k-1][0]=$assign[$j+2];
             if($nconn[$i-1] eq 'p')
             {
                $nmos[$k-2][0]=$assign[$j+2];
              }
            $pmos[$k-1][2]=$pmos[$k-3][2]=$assign[$j+2];
            $pmos[$k-2][0]=$pmos[$k-4][0];
             if($nconn[$i-1] eq 's')
            {
               $pmos[$k-2][2]=$pmos[$k-1][2];
               $pmos[$k-1][0]=$pmos[$k-2][0];
            }
          }
           
       } 
     
      $j=$j+3;
   }
   
   elsif($nconn[$i] eq 'n')
   {  
       #print"$len\n$i\n";
       if($i eq $len-1)
      { 
          for(my $u=0;$u<$lenor;$u++)
          {
             if($nmos[$u][0] eq $assign[$j])
             {
                $nmos[$u][0]=$assign[$j+1];
             }
             if($pmos[$u][2] eq $assign[$j])
             {
                 $pmos[$u][2]=$assign[$j+1];
             }
          }
       }
      else
     {
       if(length($assign[$j]) eq '1')
       {
          $nmos[$k][0]=$pmos[$k][2]='!'.$assign[$j];
          $nmos[$k][1]=$pmos[$k][1]=$assign[$j];
          $nmos[$k][2]='G';
          $pmos[$k][0]='vdd';
       }
       $k=$k+1;
     }
       
   }
 
}
my $flag=0;
   
    
   if( $nconn[$lenop-1] ne 'n')
   { 
         $flag=1;    
       $nmos[$k][1]=$nmos[$k-1][1];
       $pmos[$k][1]=$pmos[$k-1][1];
       $nmos[$k][0]=$pmos[$k][2]=$assign[$j-1];
       $nmos[$k][2]='G';   
       $pmos[$k][0]='vdd';
   }
     
     
     for(my $y=0;$y<$lenor;$y++)
     {  
       if($nmos[$y][1] eq $match[0][$y])
       {
          $nmos[$y][3]=$match[1][$y];
          if($match[1][$y] eq 1)
          {
             $pmos[$y][3]=0;
          }
          else
          {
             $pmos[$y][3]=1;
          }
       }
     }
  my $ans=scalar(@assign);
  printf"The final answer is $assign[$ans-1] : @operand1\n\n\n";
for(my $p=0;$p<($lenor+$flag);$p++)
{
  for(my $l=0;$l<=3;$l++)
   {
      print"nmos = $nmos[$p][$l]  ";
   }
   print"\n";
}
print"\n";
for(my $p=0;$p<($lenor + $flag);$p++) 
{ 
   for(my $l=0;$l<=3;$l++)
   {
       print"pmos = $pmos[$p][$l]  ";
   }
   print"\n";
}
