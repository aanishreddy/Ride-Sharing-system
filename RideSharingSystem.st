"Base class Ride"
Object subclass: #Ride
    instanceVariableNames: 'rideID pickupLocation dropoffLocation distance'

Ride >> initializeWith: id pickup: pickup dropoff: dropoff distance: dist
    rideID := id.
    pickupLocation := pickup.
    dropoffLocation := dropoff.
    distance := dist.

Ride >> fare
    self subclassResponsibility.

Ride >> rideDetails
    Transcript show: 'Ride ID: ', rideID asString, ', From: ', pickupLocation, ', To: ', dropoffLocation, ', Distance: ', distance asString; cr.

"StandardRide subclass"
Ride subclass: #StandardRide
    instanceVariableNames: ''

StandardRide >> fare
    ^ distance * 1.5.

StandardRide >> rideDetails
    super rideDetails.
    Transcript show: 'Type: Standard, Fare: $', self fare asString; cr.

"PremiumRide subclass"
Ride subclass: #PremiumRide
    instanceVariableNames: ''

PremiumRide >> fare
    ^ distance * 3.0.

PremiumRide >> rideDetails
    super rideDetails.
    Transcript show: 'Type: Premium, Fare: $', self fare asString; cr.

"Driver class"
Object subclass: #Driver
    instanceVariableNames: 'driverID name rating assignedRides'

Driver >> initializeWith: id name: driverName rating: r
    driverID := id.
    name := driverName.
    rating := r.
    assignedRides := OrderedCollection new.

Driver >> addRide: ride
    assignedRides add: ride.

Driver >> getDriverInfo
    Transcript show: 'Driver ID: ', driverID asString, ', Name: ', name, ', Rating: ', rating asString; cr.
    assignedRides do: [ :ride | ride rideDetails ].

"Rider class"
Object subclass: #Rider
    instanceVariableNames: 'riderID name requestedRides'

Rider >> initializeWith: id name: n
    riderID := id.
    name := n.
    requestedRides := OrderedCollection new.

Rider >> requestRide: ride
    requestedRides add: ride.

Rider >> viewRides
    Transcript show: 'Rider ID: ', riderID asString, ', Name: ', name; cr.
    requestedRides do: [ :ride | ride rideDetails ].

"Demo"
| r1 r2 driver rider |
r1 := StandardRide new.
r1 initializeWith: 101 pickup: 'A' dropoff: 'B' distance: 10.

r2 := PremiumRide new.
r2 initializeWith: 102 pickup: 'C' dropoff: 'D' distance: 8.

driver := Driver new.
driver initializeWith: 1 name: 'Alice' rating: 4.9.
driver addRide: r1.
driver addRide: r2.

rider := Rider new.
rider initializeWith: 201 name: 'Bob'.
rider requestRide: r1.
rider requestRide: r2.

"Output"
Transcript show: '--- Rides (Polymorphic) ---'; cr.
{r1. r2} do: [ :ride | ride rideDetails ].

Transcript show: '--- Driver Info ---'; cr.
driver getDriverInfo.

Transcript show: '--- Rider Info ---'; cr.
rider viewRides.
