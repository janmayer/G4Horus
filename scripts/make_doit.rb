puts "/run/printProgress 100000"
puts "/gun/particle gamma"

(1..300).to_a.each do |e|
	puts "/analysis/setFileName /scratch/jmayer/G4/#{e*10}"
	puts "/gun/energy #{e*10} keV"
	puts "/run/beamOn 10000000"
end
