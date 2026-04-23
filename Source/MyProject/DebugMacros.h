#pragma once
#include "DrawDebugHelpers.h"

#define DrawSphere(Location) if(GetWorld()) DrawDebugSphere(GetWorld(),Location,20.f,12,FColor::Red,true);
#define DrawSphere_Color(Location,Color) DrawDebugSphere(GetWorld(),Location,10.f,12,Color,false,5.f);
#define DrawSphere_PerFrame(Location) if(GetWorld()) DrawDebugSphere(GetWorld(),Location,20.f,12,FColor::Red,false,-1.f);
#define DrawLine(StartLocation, EndLocation) if(GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation,FColor::Red,true);
#define DrawLine_PerFrame( StartLocation, EndLocation) if(GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation,FColor::Red,false,-1.f);
#define DrawPoint(Location) if(GetWorld()) DrawDebugPoint(GetWorld(),Location,15.f,FColor::Red,true);
#define DrawPoint_PerFrame(Location) if(GetWorld()) DrawDebugPoint(GetWorld(),Location,15.f,FColor::Red,false,-1.f);
#define DrawVector(StartLocation, EndLocation) if(GetWorld()) \
{\
 DrawDebugLine(GetWorld(), StartLocation, EndLocation,FColor::Red,true);\
 DrawDebugPoint(GetWorld(),EndLocation,15.f,FColor::Red,true);\
}


#define DrawVector_PerFrame(StartLocation, EndLocation) if(GetWorld()) \
{\
 DrawDebugLine(GetWorld(), StartLocation, EndLocation,FColor::Red,false,-1.f);\
 DrawDebugPoint(GetWorld(),EndLocation,15.f,FColor::Red,false,-1.f);\
}
