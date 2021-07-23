#pragma once

#include "Core/Core.hpp"

#include "ISystem.hpp"
#include "ISubsystem.hpp"

#include "SystemTypes.hpp"
#include "SubsystemTypes.hpp"
#include "ObjectTypes.hpp"

#define SSO_CLASS(sso_type, clazz) static sso_type GetStaticType() { return Type::clazz; }