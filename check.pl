#!/usr/bin/perl
use warnings;
use strict;
my @ARGV=qw/a + b /;
my @input = split(/\s+/,$ARGV[0]);

my %inputOpPrec = ( '(' => 99, #highest precedence. Nothing would be poped
                    '+' => 4, 
                    '-' => 5 ,
                    '*' => 9 ,#pop everything on the stack higher than 9
                    '/' => 10,
                    '**' => 15 );

my %stackOpPrec = ( '(' => 0, #pop nothing and push on stack
                    '+' => 6,
                    '-' => 7, 
                    '*' => 11,
                    '/' => 12,
                    '**' => 14,#since right associative, stack prec is lower than input prec 
                   );

my @parenStack; # used to perform the parenthesis balance checker
my @stack; # used for storing operators from input

my $state = 0;
for(my $i = 0 ; $i < scalar(@input); $i++){
    my $inputSymbol = $input[$i];

    if($inputSymbol eq '(' && ($state == 0 || $state == 2) ){
        $state = 2;

        push @parenStack, '(';
        push @stack , '(';
    }
    elsif ($inputSymbol eq ')' && ($state == 1 || $state == 2)){
        $state = 1;

        # For every closing parenthesis, the rule of balancing tells us that
        # top of parenStack must be an opening paranthesis. If it is then 
        # pop the matching opening paren, if it is not then error out as it is unbalanced.
        unless (defined $parenStack[$#parenStack] && $parenStack[$#parenStack] eq '('){
               die "unbalanced parenthesis in infix expression\n";
        }else{
               delete $parenStack[$#parenStack]; 
        }

        for(my $j = $#stack; $j >= 0; $j--){
             if ($stack[$j] eq '(') {
                  delete $stack[$j];
                  last;
             }else{
                  print delete $stack[$j]; print " ";
             }
        }
    }
   elsif (exists $inputOpPrec{$inputSymbol} && $state == 1){ #is it an operator?
           $state = 0;

           #if stack is empty, push symbol onto stack and continue
           if(scalar(@stack) == 0 ){
               push @stack, $inputSymbol;
           }else{
               #from top of stack keep poping until stack symbol has lower precedence
               for(my $j = $#stack; $j >= 0; $j--){
                   my $stackSymbol = $stack[$j]; #Top stack
                   #print "input symbol: $inputSymbol\n";
                   if( $stackOpPrec{$stackSymbol} > $inputOpPrec{$inputSymbol} ){
                       print delete $stack[$j]; print " ";
                   }else{
                       last;
                   }
               }
               #we're done poping lower precedence symbols on stack
               #push onto stack the input symbol and continue with next input symbol
               push @stack, $inputSymbol;
           }
    }
    elsif($inputSymbol =~ /(?:^(-|)\d+$)/ && ($state == 0 || $state == 2)){
        $state = 1;
        print "$inputSymbol "; # it is a operand

    }
    else{
        die "Error in expression at position $i, near symbol '$inputSymbol'\n";
    }
}
if (scalar(@parenStack) > 0) {
   die "infix expression has unbalanced parantheses\n";
}
#rule 4: End of input. Pop all remaining operators
for(my $j = $#stack; $j >= 0; $j--){
   print $stack[$j]." ";
}
print "\n";
