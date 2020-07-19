#!/usr/bin/perl


start:
print "Please enter your post code: ";
$usr_post = <STDIN>;
chomp $usr_post;

open(R, '<', "random.txt");
@lines = <R>;
$i = 0;
$count = 0;
printf "Business Near You:\n";
while ($i < 4001) {
	@matching = split(/ /, $lines[$i]);
	$digit = $matching[0];
	$bus_name = $matching[2]." ".$matching[3];
	$ad = $matching[5];

	if ($usr_post == $digit || $usr_post == $digit + 10 || $usr_post == $digit - 10) {
		print "$digit\n";
		print "$bus_name $ad\n";

		$count++;
	}
	$i++;
}
printf "There are $count impacted local business near you in total\n";

#goto start;
