Camera = {}
Camera.static = 0
Camera.follow = 1

PhysxShape = {}
PhysxShape.box = 1
PhysxShape.capsule = 2
PhysxShape.sphere = 3
PhysxShape.triangle = 4
PhysxShape.convex = 5

BodyFlag = {}
BodyFlag.kinematic = 1

EntityDynamic = {}
EntityDynamic.static = 0
EntityDynamic.dynamic = 2

EntityType = {}
EntityType.physx = 0
EntityType.noPhysx = 1


Callback = {}
Callback.onStartTouch = 1
Callback.onEndTouch = 2
Callback.onTouch = 3
Callback.onImpact = 4
Callback.onStartTouchForceThreshold = 5
Callback.onEndTouchForceThreshold = 6
Callback.onTouchForceThreshold = 7

Trigger = {}
Trigger.onEnter = 1
Trigger.onLeave = 2
Trigger.onStay = 3

SoundLoop = {}
SoundLoop.once = 0
SoundLoop.loop = 1

SoundPosition = {}
SoundPosition.static = 0
SoundPosition.follow = 1

TimerType = {}
TimerType.simple = 0
TimerType.counting = 1

TimerCallback = {}
TimerCallback.Engine = 0
TimerCallback.Lua = 1

TimerCallbackMethod = {}
TimerCallbackMethod.NextStatus = 0 --przechodzi do nowego poziomu lub konczy gre

function IsBall(name)
	if name == KulaKamien or name == KulaPapier or name == KulaDrewno then
		return true
	else
		return false
	end
end

