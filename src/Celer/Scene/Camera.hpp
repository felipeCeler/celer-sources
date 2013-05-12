#ifndef LAL_CAMERA_HPP_
#define LAL_CAMERA_HPP_

#ifdef _WIN32 // _WIN32 is defined by many compilers available for the Windows operating system, but not by others.
#include <windows.h>
#endif

#include <GL/gl.h>
#include <iostream>

#include <Celer/Core/Geometry/Math/Matrix4x4.hpp>
#include <Celer/Core/Geometry/Math/Vector3.hpp>
#include <Celer/Core/Geometry/Math/Vector4.hpp>
#include <Celer/Core/Geometry/Math/Vector2.hpp>
#include <Celer/Core/Geometry/Math/Quaternion.hpp>

/*!
 *@class Camera
 *@brief Class that represent a dense 4x4 Matrix and Homogeneous Coordinate ..
 *@details coming soon , but ... coming soon  ... wait ¬¬.
 *@author Felipe Moura.
 *@version 1.0.
 *@todo OpenGL interface and a C style array, Why MakeView ans MakeProjection dont need The Transpose?
 *@todo Não deu certo integrar por que minha nova 3x3 e 4x4 matrix estavam colum major , por isso dava dando bugs ...
 *@por que eu tava armazenando em 16 variáveis e não mais nuam [][]  , e tava ido direto para colum major
 *@ resolvi o reverso depois de por assim (worldAhead * mZoomRadius) - mWorldLookAt ;
 */

// WARNING: makeCurrent must be called by every calling method
namespace Celer
{

	template < class Real >
	class Camera
	{
		public:

			typedef Celer::Quaternion<Real> Quaternion;
			typedef Celer::Matrix4x4<Real> Matrix4x4;
			typedef Celer::Vector4<Real> Vector4;
			typedef Celer::Vector3<Real> Vector3;
			typedef Celer::Vector2<int> Vector2;

			enum CameraBehavior
			{
				FIRST_PERSON, FLIGHT, REVOLVE_AROUND_MODE
			};

			Camera ( );

			Celer::Matrix4x4<Real> getViewMatrix ( );

			void getViewport ( GLint viewport[4] ) const;

			void SetBehavior ( enum CameraBehavior p );

			Celer::Vector3<Real> Focus ( );

			void SetFocus ( const Celer::Vector3<Real>& pFocus );

			Celer::Vector3<Real> Eyes ( );

			void SetEyes ( const Celer::Vector3<Real>& pEyes );

			Celer::Vector3<Real> Up ( );

			void SetUp ( const Celer::Vector3<Real>& pUp );

			Real FieldOfView ( );

			void SetFieldOfView ( const Real& pFieldOfView );

			Real AspectRatio ( );

			void SetAspectRatio ( const Real& pAspectRatio );

			void SetAspectRatio ( int width, int height );

			Real NearPlane ( );

			void SetNearPlane ( const Real& pNearPlane );

			Real FarPlane ( );

			void SetFarPlane ( const Real& pFarPlane );

			void SetProjectionMatrix ( Real pFieldOfView , Real pAspectRatio , Real pNearPlane , Real pFarPlane );

			void ComputeProjectionMatrix ( );

			void SetOrthographicProjectionMatrix ( const Real& p_left , const Real& p_right , const Real& p_bottom , const Real& p_top , const Real& p_near , const Real& p_far );

			void ComputeOrthographicProjectionMatrix ( );
			// From libQGLViewer
			void LoadProjectionMatrix ( bool reset );

			void LoadOrthographicProjectionMatrix ( bool reset );
			// From libQGLViewer
			void LoadModelViewMatrix ( bool reset );

			void MoveForward ( Real Distance );
			void MoveUpward ( Real Distance );
			void StrafeRight ( Real Distance );

			void SetMouseInfo ( int x , int y );

			void lockMouse ( bool value );

			void ComputerModelViewMatrix ( );

			Celer::Matrix4x4<Real> ViewMatrix ( );

			void SetViewByMouse ( );
			Celer::Matrix4x4<Real> ViewMatrixNormal ( );
			Celer::Matrix4x4<Real> ViewMatrix ( Celer::Vector3<Real>& pEyes , Celer::Vector3<Real>& pFocus , Celer::Vector3<Real>& pUp );

			Celer::Matrix4x4<Real> ModelViewMatrix ( );
			Celer::Matrix4x4<Real> PespectiveProjectionMatrix ( );
			Celer::Matrix4x4<Real> OrthographicProjectionMatrix ( );

			void Rotate ( Real headingDegrees , Real pitchDegrees , Real rollDegrees );
			void rotateOrbit ( Real headingDegrees , Real pitchDegrees , Real rollDegrees );

			void rotateFirstPerson ( Real headingDegrees , Real pitchDegrees );

			void LookAt ( );
			void Zoom ( Real mouseWheelDelta );
			void SetWindowSize ( int width , int height );

			void Reset ( );

		private:

			Celer::Vector3<Real> mInitalPosition;

			Celer::Quaternion<Real> mOrientation;
			Real mAccumPitchDegrees;

			Real pitchDegrees;
			Real headingDegrees;
			Real rollDegrees;

			Celer::Vector2<int> mouseLockedPosition;
			Celer::Vector2<int> mousePosition;
			bool mouseLocked;

			CameraBehavior mBehavior;

			Celer::Vector3<Real> mTarget; //Where the camera is focused
			Celer::Vector3<Real> mViewDirection; //Where the camera looked at
			Celer::Vector3<Real> mEyes; //Where the camera is. Camera position
			Celer::Vector3<Real> mUp;

			Celer::Vector3<Real> xAxis;
			Celer::Vector3<Real> yAxis;
			Celer::Vector3<Real> zAxis;

			Real mWidth;
			Real mHeight;

			Real mZoomRadius;
			Real mMinRadius;
			Real mMaxRadius;

			Celer::Matrix4x4<Real> mViewMatrix;

			// Pespective
			Real mFieldOfView;
			Real mAspectRatio;
			Real mNearPlane;
			Real mFarPlane;

			// Orthographic
			Real mLeft;
			Real mRight;
			Real mBottom;
			Real mTop;

			Real orthographicNearPlane_;
			Real orthographicFarPlane_;

			Celer::Matrix4x4<Real> mPespectiveProjectionMatrix;

			Celer::Matrix4x4<Real> mOrthographicProjectionMatrix;
	};

	template< class Real>
	Camera<Real>::Camera()
	{
		mZoomRadius = 1.0f;
		mMinRadius = 0.1f;
		mMaxRadius = 2.0f;

		mInitalPosition = Celer::Vector3<Real>(0.0,0.0,0.0);

		mOrientation = Celer::Quaternion<Real>(1.0,0.0,0.0,0.0);
		mAccumPitchDegrees = 0.0f;

		pitchDegrees = 0.0f;
		headingDegrees = 0.0f;
		rollDegrees = 0.0f;

		mouseLockedPosition.Set(0,0);
		mousePosition.Set(0,0);
		mouseLocked = 0;

		mBehavior = FIRST_PERSON;

		//Point where the camera is focused
		mTarget = Celer::Vector3<Real>(0.0,0.0,0.0);
		mViewDirection = Celer::Vector3<Real>(0.0,0.0,1.0);
		mEyes = Celer::Vector3<Real>(0.0,0.0,0.0);
		mUp = Celer::Vector3<Real>(0.0,1.0,0.0);

		mViewMatrix.Identity();

		mFieldOfView = 60.0;
		mAspectRatio = 1.0f;
		mNearPlane = 0.001f;
		mFarPlane = 100000.0f;

		orthographicNearPlane_ = -100.0;
		orthographicFarPlane_  = 100.0;

		LookAt();

	}

	template < class Real >
	Celer::Matrix4x4<Real> Camera<Real>::getViewMatrix ( )
	{
		return mViewMatrix;
	}

	template < class Real >
	void Camera<Real>::getViewport ( GLint viewport[4] ) const
	{
		viewport[0] = 0;
		viewport[1] = 0;
		viewport[2] = mWidth;
		viewport[3] = mHeight;
	}

	template < class Real >
	void Camera<Real>::SetBehavior ( enum CameraBehavior p )
	{
		mBehavior = p;
	}

	template < class Real >
	Celer::Vector3<Real> Camera<Real>::Focus ( )
	{
		return mViewDirection;
	}

	template < class Real >
	void Camera<Real>::SetFocus ( const Celer::Vector3<Real>& pFocus )
	{
		mViewDirection = pFocus;
	}

	template < class Real >
	Celer::Vector3<Real> Camera<Real>::Eyes ( )
	{
		return mEyes;

	}

	template < class Real >
	void Camera<Real>::SetEyes ( const Celer::Vector3<Real>& pEyes )
	{
		mEyes = pEyes;
	}

	template < class Real >
	Celer::Vector3<Real> Camera<Real>::Up ( )
	{
		return mUp;
	}

	template < class Real >
	void Camera<Real>::SetUp ( const Celer::Vector3<Real>& pUp )
	{
		mUp = pUp;
	}

	template < class Real >
	Real Camera<Real>::FieldOfView ( )
	{
		return mFieldOfView;
	}

	template < class Real >
	void Camera<Real>::SetFieldOfView ( const Real& pFieldOfView )
	{
		mFieldOfView = pFieldOfView;
		SetProjectionMatrix ( pFieldOfView , mAspectRatio , mNearPlane , mFarPlane );
	}

	template < class Real >
	Real Camera<Real>::AspectRatio ( )
	{
		return mAspectRatio;
	}

	template < class Real >
	void Camera<Real>::SetAspectRatio ( const Real& pAspectRatio )
	{
		mAspectRatio = pAspectRatio;
		SetProjectionMatrix ( mFieldOfView , pAspectRatio , mNearPlane , mFarPlane );
	}

	template < class Real >
	void Camera<Real>::SetAspectRatio ( int width, int height )
	{
			mAspectRatio = static_cast<Real>(width)/static_cast<Real>(height);
			SetProjectionMatrix ( mFieldOfView , mAspectRatio , mNearPlane , mFarPlane );
	}

	template < class Real >
	Real Camera<Real>::NearPlane ( )
	{
		return mNearPlane;
	}

	template < class Real >
	void Camera<Real>::SetNearPlane ( const Real& pNearPlane )
	{
		SetProjectionMatrix ( mFieldOfView , mAspectRatio , pNearPlane , mFarPlane );
	}

	template < class Real >
	Real Camera<Real>::FarPlane ( )
	{
		return mFarPlane;
	}

	template < class Real >
	void Camera<Real>::SetFarPlane ( const Real& pFarPlane )
	{
		SetProjectionMatrix ( mFieldOfView , mAspectRatio , mNearPlane , pFarPlane );
	}

	template < class Real >
	void Camera<Real>::SetProjectionMatrix ( Real pFieldOfView , Real pAspectRatio , Real pNearPlane , Real pFarPlane )
	{
		mFieldOfView = pFieldOfView;

		mAspectRatio = pAspectRatio;
		mNearPlane = pNearPlane;
		mFarPlane = pFarPlane;

		mPespectiveProjectionMatrix = Celer::Matrix4x4<Real>::MakePespectiveProjectionMatrix ( mFieldOfView * mZoomRadius , mAspectRatio , mNearPlane , mFarPlane );
	}

	template < class Real >
	void Camera<Real>::ComputeProjectionMatrix ( )
	{
		mPespectiveProjectionMatrix = Celer::Matrix4x4<Real>::MakePespectiveProjectionMatrix ( mFieldOfView * mZoomRadius , mAspectRatio , mNearPlane , mFarPlane );
	}

	template < class Real >
	void Camera<Real>::SetOrthographicProjectionMatrix ( const Real& p_left , const Real& p_right , const Real& p_bottom , const Real& p_top , const Real& p_near , const Real& p_far )
	{
		mLeft = p_left;
		mRight = p_right;
		mBottom = p_bottom;
		mTop = p_top;

		orthographicNearPlane_ = p_near;
		orthographicFarPlane_ = p_far;

		mOrthographicProjectionMatrix = Celer::Matrix4x4<Real>::MakeOrthographicProjectionMatrix ( mLeft , mRight , mBottom , mTop , orthographicNearPlane_ , orthographicFarPlane_);
	}

	template < class Real >
	void Camera<Real>::ComputeOrthographicProjectionMatrix ( )
	{
		mOrthographicProjectionMatrix = Celer::Matrix4x4<Real>::MakeOrthographicProjectionMatrix ( mLeft , mRight , mBottom , mTop , orthographicNearPlane_ , orthographicFarPlane_);
	}

//	// From libQGLViewer
	template < class Real >
	void Camera<Real>::LoadProjectionMatrix ( bool reset = 1 )
	{
		glMatrixMode ( GL_PROJECTION );

		if ( reset )
			glLoadIdentity ( );

		ComputeProjectionMatrix ( );
		glMultMatrixf ( ( ~mPespectiveProjectionMatrix ).ToRealPtr ( ) );

//		std::cout << "mFieldOfView :" << mFieldOfView  << std::endl;
//		std::cout << "mAspectRatio :" << mAspectRatio << std::endl;
//		std::cout << "mNearPlane :" << mNearPlane << std::endl;
//		std::cout << "mFarPlane :" << mFarPlane << std::endl;
	}

	template < class Real >
	void Camera<Real>::LoadOrthographicProjectionMatrix ( bool reset = 1 )
	{
		glMatrixMode ( GL_PROJECTION );

		if ( reset )
			glLoadIdentity ( );

		ComputeOrthographicProjectionMatrix ( );
		glMultMatrixf ( ( ~mOrthographicProjectionMatrix ).ToRealPtr ( ) );
	}

//	// From libQGLViewer
	template < class Real >
	void Camera<Real>::LoadModelViewMatrix ( bool reset = 1 )
	{
		// WARNING: makeCurrent must be called by every calling method
		glMatrixMode ( GL_MODELVIEW );
		glLoadIdentity ( );
		ComputerModelViewMatrix ( );
		if ( reset )
			glLoadMatrixf ( ( ~mViewMatrix ).ToRealPtr ( ) );
		else
			glMultMatrixf ( ( ~mViewMatrix ).ToRealPtr ( ) );
	}

	template < class Real >
	void Camera<Real>::MoveForward ( Real Distance )
	{
		mEyes += ( mViewDirection * Distance );
	}

	template < class Real >
	void Camera<Real>::MoveUpward ( Real Distance )
	{
		mEyes += ( mUp * Distance );
	}

	template < class Real >
	void Camera<Real>::StrafeRight ( Real Distance )
	{
		mEyes += ( ( mViewDirection ) ^ mUp ) * Distance;
	}

	template < class Real >
	void Camera<Real>::SetMouseInfo ( int x , int y )
	{
		mousePosition.Set ( x , y );
	}

	template < class Real >
	void Camera<Real>::lockMouse ( bool value )
	{
		if ( value )
		{
			mouseLockedPosition = mousePosition;
		}

		mouseLocked = value;
	}

	template < class Real >
	void Camera<Real>::ComputerModelViewMatrix ( )
	{

		mViewMatrix = mOrientation.To4x4Matrix ( );

		xAxis.Set ( mViewMatrix[0][0] , mViewMatrix[0][1] , mViewMatrix[0][2] );
		yAxis.Set ( mViewMatrix[1][0] , mViewMatrix[1][1] , mViewMatrix[1][2] );
		zAxis.Set ( mViewMatrix[2][0] , mViewMatrix[2][1] , mViewMatrix[2][2] );

		mViewDirection = -zAxis;

		if ( mBehavior == REVOLVE_AROUND_MODE )
		{
			// Calculate the new camera position based on the current
			// orientation. The camera must always maintain the same
			// distance from the target. Use the current offset vector
			// to determine the correct distance from the target.

			mEyes = mTarget + ( zAxis * 7.0f );
		}

		mViewMatrix[0][3] -= ( xAxis * mEyes );
		mViewMatrix[1][3] -= ( yAxis * mEyes );
		mViewMatrix[2][3] -= ( zAxis * mEyes );

	}

	template < class Real >
	Celer::Matrix4x4<Real> Camera<Real>::ViewMatrix ( )
	{

		mViewMatrix = mOrientation.To4x4Matrix ( );

		xAxis.Set ( mViewMatrix[0][0] , mViewMatrix[0][1] , mViewMatrix[0][2] );
		yAxis.Set ( mViewMatrix[1][0] , mViewMatrix[1][1] , mViewMatrix[1][2] );
		zAxis.Set ( mViewMatrix[2][0] , mViewMatrix[2][1] , mViewMatrix[2][2] );

		mViewDirection = -zAxis;

		if ( mBehavior == REVOLVE_AROUND_MODE )
		{
			// Calculate the new camera position based on the current
			// orientation. The camera must always maintain the same
			// distance from the target. Use the current offset vector
			// to determine the correct distance from the target.

			mEyes = mTarget + ( zAxis * 3.0f );
		}

		mViewMatrix[0][3] = - ( xAxis * mEyes );
		mViewMatrix[1][3] = - ( yAxis * mEyes );
		mViewMatrix[2][3] = - ( zAxis * mEyes );
		//LookAt();
		return mViewMatrix; //ViewMatrixNormal();

	}

	template < class Real >
	void Camera<Real>::SetViewByMouse ( )
	{
		Real pitch = 0.0f, heading = 0.0f;

		if ( ( mousePosition == mouseLockedPosition ) || !mouseLocked )
		{
			return;
		}

		pitch = Real ( mouseLockedPosition.x - mousePosition.x ) * Math::kDeg2Rad * 0.2;
		heading = Real ( mouseLockedPosition.y - mousePosition.y ) * Math::kDeg2Rad * 0.2;

		Rotate ( -heading , -pitch , 0.0f );

		if ( !mouseLocked )
		{
			mouseLockedPosition = mousePosition;
		}

	}

	template < class Real >
	Celer::Matrix4x4<Real> Camera<Real>::ViewMatrixNormal ( )
	{

		return Celer::Matrix4x4<Real>::MakeViewMatrix ( mEyes , mViewDirection , mUp );

	}

	template < class Real >
	Celer::Matrix4x4<Real> Camera<Real>::ViewMatrix ( Celer::Vector3<Real>& pEyes , Celer::Vector3<Real>& pFocus , Celer::Vector3<Real>& pUp )
	{
		return Celer::Matrix4x4<Real>::MakeViewMatrix ( pEyes , pFocus , pUp );
	}

	template < class Real >
	Celer::Matrix4x4<Real> Camera<Real>::ModelViewMatrix ( )
	{
		return mViewMatrix;
	}

	template < class Real >
	Celer::Matrix4x4<Real> Camera<Real>::PespectiveProjectionMatrix ( )
	{
		return mPespectiveProjectionMatrix;
	}

	template < class Real >
	Celer::Matrix4x4<Real> Camera<Real>::OrthographicProjectionMatrix ( )
	{
		return mOrthographicProjectionMatrix;
	}

	template < class Real >
	void Camera<Real>::Rotate ( Real headingDegrees , Real pitchDegrees , Real rollDegrees )
	{
		// Rotates the camera based on its current behavior.
		// Note that not all behaviors support rolling.

		pitchDegrees = -pitchDegrees;
		headingDegrees = -headingDegrees;
		rollDegrees = -rollDegrees;

		switch ( mBehavior )
		{
			case FIRST_PERSON:
				rotateFirstPerson ( headingDegrees , pitchDegrees );
				break;

			case REVOLVE_AROUND_MODE:
				rotateOrbit ( headingDegrees , pitchDegrees , rollDegrees );
				break;
			default:
				break;
		}

	}

	template < class Real >
	void Camera<Real>::rotateOrbit ( Real headingDegrees , Real pitchDegrees , Real rollDegrees )
	{
		// Implements the rotation logic for the orbit style camera behavior.
		// Roll is ignored for target Y axis orbiting.
		//
		// Briefly here's how this orbit camera implementation works. Switching to
		// the orbit camera behavior via the setBehavior() method will set the
		// camera's orientation to match the orbit target's orientation. Calls to
		// rotateOrbit() will rotate this orientation. To turn this into a third
		// person style view the updateViewMatrix() method will move the camera
		// position back 'm_orbitOffsetDistance' world units along the camera's
		// local z axis from the orbit target's world position.

		Celer::Quaternion<Real> rot;

		if ( headingDegrees != 0.0f )
		{
			rot.FromAxisAngle ( Celer::Vector3<Real>::UNIT_Y , headingDegrees );
			mOrientation = mOrientation * rot;
		}

		if ( pitchDegrees != 0.0f )
		{
			rot.FromAxisAngle ( Celer::Vector3<Real>::UNIT_X , pitchDegrees );
			mOrientation = rot * mOrientation;
		}
		mOrientation.Normalize ( );
	}

	template < class Real >
	void Camera<Real>::rotateFirstPerson ( Real headingDegrees , Real pitchDegrees )
	{
		// Implements the rotation logic for the first person style and
		// spectator style camera behaviors. Roll is ignored.

		mAccumPitchDegrees += pitchDegrees;

		if ( mAccumPitchDegrees > 90.0f )
		{
			pitchDegrees = 90.0f - ( mAccumPitchDegrees - pitchDegrees );
			mAccumPitchDegrees = 90.0f;
		}

		if ( mAccumPitchDegrees < -90.0f )
		{
			pitchDegrees = -90.0f - ( mAccumPitchDegrees - pitchDegrees );
			mAccumPitchDegrees = -90.0f;
		}

		Celer::Quaternion<Real> rot;

		// Rotate camera about the world y axis.
		// Note the order the quaternions are multiplied. That is important!
		if ( headingDegrees != 0.0f )
		{
			rot.FromAxisAngle ( Celer::Vector3<Real>::UNIT_Y , headingDegrees );
			mOrientation = mOrientation * rot;
		}

		// Rotate camera about its local x axis.
		// Note the order the quaternions are multiplied. That is important!
		if ( pitchDegrees != 0.0f )
		{
			rot.FromAxisAngle ( Celer::Vector3<Real>::UNIT_X , pitchDegrees );
			mOrientation = rot * mOrientation;
		}
		mOrientation.Normalize ( );
	}

	template < class Real >
	void Camera<Real>::LookAt ( )
	{

		zAxis = mViewDirection;
		zAxis.Normalize ( );

		xAxis = ( mUp ^ zAxis );
		xAxis.Normalize ( );

		yAxis = ( zAxis ^ xAxis );
		yAxis.Normalize ( );

		mViewMatrix[0][0] = xAxis.x;
		mViewMatrix[0][1] = xAxis.y;
		mViewMatrix[0][2] = xAxis.z;
		mViewMatrix[0][3] = - ( xAxis * mEyes );

		mViewMatrix[1][0] = yAxis.x;
		mViewMatrix[1][1] = yAxis.y;
		mViewMatrix[1][2] = yAxis.z;
		mViewMatrix[1][3] = - ( yAxis * mEyes );

		mViewMatrix[2][0] = zAxis.x;
		mViewMatrix[2][1] = zAxis.y;
		mViewMatrix[2][2] = zAxis.z;
		mViewMatrix[2][3] = - ( zAxis * mEyes );

		// Extract the pitch angle from the view matrix.
		mAccumPitchDegrees = Math::kRad2Deg * ( std::asin ( mViewMatrix[2][1] ) );

		mOrientation.FromRotationMatrix ( mViewMatrix );
	}

	template < class Real >
	void Camera<Real>::Zoom ( Real mouseWheelDelta )
	{
	     // Change the radius from the camera to the model based on wheel scrolling
	     // mZoomRadius -= mouseWheelDelta * 0.1f;

	     // std::cout << "Wheel "<< mouseWheelDelta << " zoom  "<< mZoomRadius <<  std::endl;
	     // mZoomRadius  = std::min<Real> ( mMaxRadius, mZoomRadius );
	     // mZoomRadius  = std::max<Real> ( mMinRadius, mZoomRadius );

	     mViewDirection.z -= 0.2;
	}

	template < class Real >
	void Camera<Real>::SetWindowSize ( int width , int height )
	{
		mWidth = width;
		mHeight = height;

	}

	template < class Real >
	void Camera<Real>::Reset ( )
	{
		mEyes = mInitalPosition;

	}

}/* Celer :: NAMESPACE */

#endif /*CAMERA_HPP_*/
