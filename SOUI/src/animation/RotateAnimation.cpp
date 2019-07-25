
#include <souistd.h>
#include <animation/RotateAnimation.h>

namespace SOUI {



	void SRotateAnimation::initialize(int width, int height, int parentWidth, int parentHeight) 
	{
		mPivotX = (float)resolveSize(mPivotXType, mPivotXValue, width, parentWidth);
		mPivotY = (float)resolveSize(mPivotYType, mPivotYValue, height, parentHeight);
	}

	void SRotateAnimation::copy(const IAnimation *src)
	{
		SAnimation::copy(src);
		SRotateAnimation * src2 = sobj_cast<SRotateAnimation>(src);
		mFromDegrees = src2->mFromDegrees;
		mToDegrees = src2->mToDegrees;

		mPivotXType = src2->mPivotXType;
		mPivotYType = src2->mPivotYType;
		mPivotXValue = src2->mPivotXValue;
		mPivotYValue = src2->mPivotYValue;
	}

	void SRotateAnimation::applyTransformation(float interpolatedTime, STransformation & t)
	{
		float degrees = mFromDegrees + ((mToDegrees - mFromDegrees) * interpolatedTime);
		float scale = getScaleFactor();

		if (mPivotX == 0.0f && mPivotY == 0.0f) {
			t.getMatrix().setRotate(degrees);
		}
		else {
			t.getMatrix().setRotate(degrees, mPivotX * scale, mPivotY * scale);
		}
		t.setTransformationType(STransformation::TYPE_MATRIX);
	}

	void SRotateAnimation::initializePivotPoint()
	{
		if (mPivotXType == ABSOLUTE_VALUE) {
			mPivotX = mPivotXValue;
		}
		if (mPivotYType == ABSOLUTE_VALUE) {
			mPivotY = mPivotYValue;
		}
	}

	SRotateAnimation::SRotateAnimation(float fromDegrees, float toDegrees, ValueType pivotXType, float pivotXValue, ValueType pivotYType, float pivotYValue) 
	{
		mFromDegrees = fromDegrees;
		mToDegrees = toDegrees;

		mPivotXValue = pivotXValue;
		mPivotXType = pivotXType;
		mPivotYValue = pivotYValue;
		mPivotYType = pivotYType;
		initializePivotPoint();
	}

	SRotateAnimation::SRotateAnimation(float fromDegrees, float toDegrees, float pivotX, float pivotY)
	{
		mFromDegrees = fromDegrees;
		mToDegrees = toDegrees;

		mPivotXType = ABSOLUTE_VALUE;
		mPivotYType = ABSOLUTE_VALUE;
		mPivotXValue = pivotX;
		mPivotYValue = pivotY;
		initializePivotPoint();
	}

	SRotateAnimation::SRotateAnimation(float fromDegrees/*=0.0f*/, float toDegrees/*=0.0f*/) 
	{
		mFromDegrees = fromDegrees;
		mToDegrees = toDegrees;
		mPivotX = 0.0f;
		mPivotY = 0.0f;
	}

}