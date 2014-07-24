puts "/run/printProgress 100000"

(1..100).to_a.each do |e|
	puts "/analysis/setFileName /scratch/jmayer/G4/#{e*100}"
	puts "/gun/energy #{e*100} keV"
	puts "/run/beamOn 10000000"
end