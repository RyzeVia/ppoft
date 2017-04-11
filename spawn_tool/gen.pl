#!/usr/bin/perl

use strict;

sub parse_arg($$$$$){
  my ($types, $names, $t0, $n, $t1) = @_;
  my $t;
  my $p = "";
  
#  print "@$types, @$names, $t0, $n, $t1\n";
  
  if($t0){
    $t = $t0;
    $t =~ s/\s+$//;
  }else{
    $t = $t1;
    $n = "arg" . (1 + scalar(@$types));
  }
  push(@$types, $t);
  push(@$names, $n);
  if($t =~ /\[\]/){
    my $tt = $t;
    $tt =~ s/\[\]//;
    "$tt $n" . "[]";
  } else {
    "$t $n";
  }
}

my $mpiheaders = '/opt/FJSVfxlang/GM-1.2.1-09/include/mpi/fujitsu/mpi.h';
my $command = 'which mpicc | sed -e'." \'".'s/bin\/mpicc$/include\/mpi.h/'."\'";
#print $command;
my $defhead = `$command`;
#print $defhead;
print '#include <mpi.h>', $/;
#print '#include <stdio.h>', $/;
#print '#include <sys/types.h>', $/;
#print '#include <unistd.h>', $/;

print 'extern MPI_Comm MPI_COMM_SMALLER_WORLD;', $/;
print 'extern void spawn_debug_start(char *fname);', $/;
my $fh;
my $flag = 0;
my $mpich = 0;
open($fh, $mpiheaders) ||
open($fh,$defhead);
# || open($fh,$ARGV[0]);

while(<$fh>){
  chomp;
  if(/(MPI API|MPICH_SUPPRESS_PROTOTYPES)/){
    if(/MPICH_SUPPRESS_PROTOTYPES/){
      $mpich = 1;
    }
    last if $flag == 1;
    ++ $flag if $flag == 0;
  }elsif($flag && / MPI_/){
    my $f = $_;
    while(! /;/){
      $_ = <$fh>;
      chomp;
      s/^\s+//;
      $f .= $_;
    }
    #print "FFF $f FFF\n";
    $f =~ s/^OMPI_DECLSPEC\s+//;
    $f =~ /^(\w+[\s\*\[\]]+)(\w+)\s*\((.*?)\)/;
    my $returntype = $1;
    my $funcname = $2;
    my $args = $3;
    
    $args =~ s/const\s/constand/g;
    
    next if $funcname =~ /spawn/;
    next if $funcname =~ /Abort/;
    next if $mpich && ($funcname eq "MPI_Comm_c2f");
    #print "X $returntype X $funcname X $args X\n";
    if($args =~ /MPI_Comm(\s+\w|\s*(,|$))/){
      my $argtypes = [];
      my $argnames = [];
      $args =~ s/((\w+[\s\*\[\]]+)(\w+)|(\w+[\s\*\[\]]*))/parse_arg($argtypes, $argnames, $2, $3, $4)/eg;
      $args =~ s/constand/const /g;
      print "$returntype$funcname($args){\n";
      
      print "#ifdef DEBUG_WRAPPING\n";
      print 'spawn_debug_start(__FUNCTION__);';
      print "\n#endif\n";
      
      
      for(my $i = 0; $i < scalar(@$argtypes); ++ $i){
        my $t = $argtypes->[$i];
        #$t =~ s/\s+$//;
        if($t =~ /^MPI_Comm\s*$/ ){
          my $n = $argnames->[$i];
          #print 'printf("ON\n");';
          print "  if($n == MPI_COMM_WORLD){$n = MPI_COMM_SMALLER_WORLD;}\n";
        }
      }
      print "  return P$funcname(", join(",",@$argnames), ");\n";
      print "}", $/
    }
  }
}
