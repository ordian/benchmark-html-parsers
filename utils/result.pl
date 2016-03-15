#!/usr/bin/perl -w

use utf8;
use strict;

my @files = qw|
	/new/html_parsers/result/myhtml_single.csv
	/new/html_parsers/result/myhtml.csv
	/new/html_parsers/result/html5ever.csv
	/new/html_parsers/result/gumbo.csv
|;

my $work_result = work(\@files);

save_work($work_result, "/new/html_parsers/benchmark_time",   0, 100, "time");
save_work($work_result, "/new/html_parsers/benchmark_time", 100, 200, "time");
save_work($work_result, "/new/html_parsers/benchmark_time", 200, 300, "time");
save_work($work_result, "/new/html_parsers/benchmark_time", 300, 400, "time");
save_work($work_result, "/new/html_parsers/benchmark_time", 400, 500, "time");

save_work($work_result, "/new/html_parsers/benchmark_mem",   0, 100, "mem");
save_work($work_result, "/new/html_parsers/benchmark_mem", 100, 200, "mem");
save_work($work_result, "/new/html_parsers/benchmark_mem", 200, 300, "mem");
save_work($work_result, "/new/html_parsers/benchmark_mem", 300, 400, "mem");
save_work($work_result, "/new/html_parsers/benchmark_mem", 400, 500, "mem");

save_work($work_result, "/new/html_parsers/benchmark_time", 0, 500, "time");
save_work($work_result, "/new/html_parsers/benchmark_mem" , 0, 500, "mem");

sub save_work {
	my ($work_result, $dirpath, $from, $to, $who) = @_;
	
	open my $fh, ">", "$dirpath/benchmark_$from\_$to.csv" or die "Can't open file for save data: $!";
	binmode $fh, ":utf8";
	
	save_to_csv($work_result, $fh, $from, $to, $who);
	
	close $fh;
}

sub work {
	my ($files) = @_;
	
	my $result;
	
	foreach my $filename (@$files) {
		my $res = make_hash( read_file($filename) );
		my $parser_name = make_name_from_filename($filename);
		
		foreach my $name (keys %$res) {
			$result->{$name}->{mem}->{ $parser_name } = $res->{$name}[2];
			$result->{$name}->{time}->{ $parser_name } = $res->{$name}[1];
		}
	}
	
	$result;
}

sub save_to_csv {
	my ($result, $fh, $begin, $end, $who) = @_;
	
	my $name = (sort {$a cmp $b} keys %$result)[0];
	print $fh "name;", join(";", (sort {$a cmp $b} keys %{$result->{$name}->{$who}})), "\n";
	
	my $count = 0;
	foreach my $name (sort {$a cmp $b} keys %$result) {
		next if $count++ < $begin;
		last if $count > $end;
		
		print $fh "\"$name\";";
		
		my @vals = map { $result->{$name}->{$who}->{$_} } (sort {$a cmp $b} keys %{$result->{$name}->{$who}});
		
		print $fh join(";", @vals);
		print $fh "\n";
	}
}

sub read_file {
	my ($filename) = @_;
	
	open my $fh, "<", $filename or die "Can't open file $filename: $!";
	my @lines = <$fh>;
	close $fh;
	
	\@lines;
}

sub make_hash {
	my ($lines) = @_;
	
	my $hash = {};
	foreach my $line (@$lines) {
		$line =~ s/\s+$//;
		
		my ($filename, $filesize, $parse_time, $mem_used) = split /\s*;\s*/, $line;
		
		$filename =~ s/^"//; $filename =~ s/"$//;
		
		my $name = make_name_from_filename($filename);
		$hash->{$name} = [$filesize, $parse_time, $mem_used];
	}
	
	$hash;
}

sub make_name_from_filename {
	$_[0] =~ /([^\/]+)\.(?:html|csv)/;
	$1;
}

