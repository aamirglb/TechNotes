print "Enter a temperate in Celsius:\n";
$c = <STDIN>;
chomp($c);

#if($c =~ m/^[0-9]+\.*[0-9]*$/) {
if($c =~ m/^[-+]?[0-9]+(\.[0-9]*)?$/) {
    $f = ($c * 9 / 5) + 32;
    print "$c C is $f F\n";
} else {
    print "Expecting a number, so I don't understand \"$c\".\n";
}