#/usr/bin/perl

use strict;
my @pragma = ();
my @ext = ();
my $funcname = '';

my $pflag = 0;
my $fflag = 0;
my $cflag = 0;
my $eflag = 0;
my $fn = '';
my $wfn = '';
my $wfn2 = '';
my $ret = '';
my $argc = 0;
my $work = '';
my @ct;

my $line = '';


#print <<'EOM';
##include <stdio.h>
##include <stdlib.h>
##include "mpi.h"
#
#
#EOM

open(FILE, "./fbindings_special.data") or die "file not found\n";
@ct = <FILE>;
close(FILE);

print "#ifdef MPICH_VERSION\n";

foreach $line (@ct){
	chomp($line);
#	print "L:$line\n";
	
	if ($line =~ /^FUNCTION_NAME,([^,]*)/){
		$funcname = $1;
#		print "F:$funcname\n";
		$fflag = -1;
		next;
	}	
	if ($line =~ /^PRAGMA_DEFINITION/){
		$pflag = 1;
		next;
	}
	if ($line =~ /^END_PRAGMA_DEFINITION/){
		$pflag = -1;
		next;
	}
	if ($line =~ /^EXTERN_DEFINITION/){
		$eflag = 1;
		next;
	}
	if ($line =~ /^END_EXTERN_DEFINITION/){
		$eflag = -1;
		next;
	}	
	if ($line =~ /^FUNCTION_CONTENTS/){
		$cflag = 1;
		next;
	}
	if ($line =~ /^END_FUNCTION_CONTENTS/){
		$cflag = -1;
		next;
	}
	
	if($pflag == 1){
#		print "P";
		push(@pragma, $line);
		next;
	}
	
	if($eflag == 1){
#		print "E";
		push(@ext, $line);
		next;
	}
	
	if($cflag == 1){
#		print "C";
		make_function($line);
	}
}

print "#endif\n";

exit;

sub make_function{
	my $cont = shift;
#	print "C2:$cont";
	my $function = '';
	my $extern = '';
	if($cont =~ /^([^,]*),([^,]*),([0-9]*)$/i ){

		$fn = $1;
		$ret = $2;
		$argc = $3;

#		print "$cont: $fn, $ret, $argc\n";

		foreach my $pg (@pragma){
			$work = $pg;
			$fn=lc($fn);
			$work =~ s/xxx/$fn/g;
			$fn=uc($fn);
			$work =~ s/XXX/$fn/g;
			$fn = ucfirst(lc($fn));
			$work =~ s/Xxx/$fn/g;
			$fn = lc($fn);
			print "#pragma weak $work\n";
		}

		$work = $funcname;
			$fn=lc($fn);
			$work =~ s/xxx/$fn/g;
			$fn=uc($fn);
			$work =~ s/XXX/$fn/g;
			$fn = ucfirst(lc($fn));
			$work =~ s/Xxx/$fn/g;
			$fn = lc($fn);

		$function = "$ret $work (";
		
		for(my $i = 1; $i < $argc; $i++){
			$function.= "void* v$i,";
		}
		$function .= "MPI_Fint* v$argc)\n";

#		print "test:".$function."\n";
		chomp($function);
		$wfn = $work;
#		print "test: $wfn\n";
		$extern = $function.';'."\n";
		$work = $extern;
		foreach my $et (@ext){
#			print "$et:$fn\n";
			$wfn2 = $et;
			$fn=lc($fn);
			$wfn2 =~ s/xxx/$fn/g;
			$fn=uc($fn);
			$wfn2 =~ s/XXX/$fn/g;
			$fn = ucfirst(lc($fn));
			$wfn2 =~ s/Xxx/$fn/g;
			$fn = lc($fn);
			
			
#			print "A:$work";
			$work =~ s/$wfn/$wfn2/g;
#			print "B:$work";
			print $work;
			$work = $extern;
		}
		#wait
		print $function;
		
		
	}else{
		if(($fflag == -1) && ($pflag == -1)){
			print "$cont\n";		
		}
	}
}

1;
	


