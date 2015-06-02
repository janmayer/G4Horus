#!/usr/bin/env ruby

puts "/run/printProgress 100000"
puts "/gun/particle gamma"

(1..100).to_a.each do |e|
	puts "/analysis/setFileName #{e*25}"
	puts "/gun/energy #{e*25} keV"
	puts "/run/beamOn 10000000"
end
