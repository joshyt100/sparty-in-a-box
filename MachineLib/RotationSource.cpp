/**
 * @file RotationSource.cpp
 * @author Josh Thomas
 */

#include "pch.h"
#include "RotationSource.h"

#include "RotationSink.h"

void RotationSource::SetRotation(double rotation) {
 mRotation = rotation;
 PropagateRotation();
}

void RotationSource::AddSink(std::shared_ptr<RotationSink> sink) {
 mSinks.push_back(sink);
}

void RotationSource::PropagateRotation() {
 for (const auto &sink : mSinks) {
  sink->SetRotation(mRotation);
 }
}