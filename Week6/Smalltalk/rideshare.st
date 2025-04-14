"===== Ride Class ====="
Object subclass: Ride [
    | rideID pickupLocation dropoffLocation distance |

    Ride class >> newRideWithID: id pickup: pickup dropoff: dropoff distance: dist [
        | r |
        r := self new.
        r initializeRideWithID: id pickup: pickup dropoff: dropoff distance: dist.
        ^ r
    ]

    Ride >> initializeRideWithID: id pickup: pickup dropoff: dropoff distance: dist [
        rideID := id.
        pickupLocation := pickup.
        dropoffLocation := dropoff.
        distance := dist.
    ]

    Ride >> fare [
        ^ distance * 2.
    ]

    Ride >> rideDetails [
        ^ 'Ride ID: ', rideID asString,
           ' | Pickup: ', pickupLocation,
           ' | Dropoff: ', dropoffLocation,
           ' | Distance: ', distance asString, ' miles',
           ' | Fare: $', self fare printString.
    ]
]

"===== StandardRide Class ====="
Ride subclass: StandardRide [
    StandardRide >> fare [
        ^ distance * 2.
    ]
]

"===== PremiumRide Class ====="
Ride subclass: PremiumRide [
    PremiumRide >> fare [
        ^ (distance * 3.5) + 5.
    ]
]

"===== Driver Class ====="
Object subclass: Driver [
    | driverID name rating assignedRides |

    Driver class >> newDriverWithID: id name: driverName rating: rate [
        | d |
        d := self new.
        d initializeWithID: id name: driverName rating: rate.
        ^ d
    ]

    Driver >> initializeWithID: id name: driverName rating: rate [
        driverID := id.
        name := driverName.
        rating := rate.
        assignedRides := OrderedCollection new.
    ]

    Driver >> addRide: aRide [
        assignedRides add: aRide.
    ]

    Driver >> driverInfo [
        ^ 'Driver ID: ', driverID asString,
           ' | Name: ', name,
           ' | Rating: ', rating asString,
           ' | Assigned Rides: ', assignedRides size asString.
    ]
]

"===== Rider Class ====="
Object subclass: Rider [
    | riderID name requestedRides |

    Rider class >> newRiderWithID: id name: riderName [
        | r |
        r := self new.
        r initializeWithID: id name: riderName.
        ^ r
    ]

    Rider >> initializeWithID: id name: riderName [
        riderID := id.
        name := riderName.
        requestedRides := OrderedCollection new.
    ]

    Rider >> requestRide: aRide [
        requestedRides add: aRide.
    ]

    Rider >> viewRides [
        ('Ride history for Rider ID: ', riderID asString, ' (', name, ')') displayNl.
        requestedRides do: [:ride |
            ride rideDetails displayNl.
        ].
    ]
]

"===== Demo Script ====="
| ride1 ride2 driver1 driver2 rider1 |

ride1 := StandardRide newRideWithID: 101 pickup: 'Mt Juliet' dropoff: 'Nashville' distance: 15.
ride2 := PremiumRide newRideWithID: 102 pickup: 'Wall Street' dropoff: 'Broadway' distance: 7.

'Demonstrating Polymorphism with Ride Details:' displayNl.
{ ride1. ride2 } do: [:r |
    r rideDetails displayNl.
].

driver1 := Driver newDriverWithID: 1 name: 'Arun' rating: 5.9.
driver1 addRide: ride1.
driver1 driverInfo displayNl.

driver2 := Driver newDriverWithID: 2 name: 'Gadde' rating: 5.6.
driver2 addRide: ride2.
driver2 driverInfo displayNl.

rider1 := Rider newRiderWithID: 1 name: 'Sravya'.
rider1 requestRide: ride1.
rider1 requestRide: ride2.
rider1 viewRides.
