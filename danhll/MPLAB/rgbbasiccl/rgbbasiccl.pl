#! c:\perl\bin\perl -w
use strict;

   
use Win32::SerialPort;

my ($addr, $rled, $gled, $bled);
my $checksum;
my $start=  0x81;
my ($byte1, $byte2, $byte3, $byte4, $byte5, $byte6);
my ($rdir, $gdir, $bdir);
my $yes;
	

my $Config_File = "basic2400.cfg";
my $baud = "2400";
my $port = "COM1";
my $parity = "none";
my $databits = "8";
my $stopbits = "1";
my $handshake = "none";

$|=1; 


my $PortObj = new Win32::SerialPort ($port)
       || die "Can't open $port: $^E\n";    # $quiet is optional


  $PortObj->baudrate($baud);
  $PortObj->parity($parity);
  $PortObj->databits($databits);
  $PortObj->stopbits($stopbits);
  #$PortObj->handshake($handshake);
  $PortObj->buffers(6, 6);
  $PortObj->write_char_time(0);
  $PortObj->write_const_time(0);
  $PortObj->is_binary(0);
  #$PortObj->datatype('raw');

  #use open IN => ":raw", OUT => ":raw";

  $PortObj->write_settings || undef $PortObj;
  
  $PortObj->save($Config_File)
       || warn "Can't save $Config_File: $^E\n";
       
 $PortObj->close || die "failed to close";
  undef $PortObj; 

  my $tie_ob = tie(*PORT,'Win32::SerialPort', $Config_File)
                 or die "Can't start $Config_File\n";
    
    while (1){
        
        print "Enter Red data byte 2 : ";
        $rled = <STDIN>;
        chomp $rled;

        print "Enter Green data byte 3 : ";
        $gled = <STDIN>;
        chomp $gled;
        
        print "Enter Blue data byte 4 : ";
        $bled = <STDIN>;
        chomp $bled;
        
        
        $checksum = ((($start + $rled + $gled + $bled)^255 )+1) & 255;

        
	my $data = chr($start) .chr($rled) .chr($gled) .chr($bled) .chr($checksum);

     
	    syswrite PORT, $data;


        print "-------------------------------\n";
        print "\n";
        

    }
        
        

	
 
 
  

 
 
