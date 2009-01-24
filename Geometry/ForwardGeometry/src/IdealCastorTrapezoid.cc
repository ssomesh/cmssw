#include "Geometry/ForwardGeometry/interface/IdealCastorTrapezoid.h"
#include <math.h>

namespace calogeom {

   std::vector<HepPoint3D>
   IdealCastorTrapezoid::localCorners( const double* pv  ,
				       HepPoint3D&   ref   )
   {
      assert( 0 != pv ) ;

      const double dx ( pv[0] ) ;
      const double dy ( pv[1] ) ;
      const double dz ( pv[2] ) ;

      std::vector<GlobalPoint> gc ( 8, GlobalPoint(0,0,0) ) ;
      std::vector<HepPoint3D>  lc ( 8, HepPoint3D( 0,0,0) ) ;

      gc[ 0 ] = GlobalPoint( -dx, -dy, -dz ) ; 
      gc[ 1 ] = GlobalPoint( -dx, +dy, -dz ) ; 
      gc[ 2 ] = GlobalPoint( +dx, +dy, -dz ) ; 
      gc[ 3 ] = GlobalPoint( +dx, -dy, -dz ) ; 
      gc[ 4 ] = GlobalPoint( -dx, -dy, +dz ) ; 
      gc[ 5 ] = GlobalPoint( -dx, +dy, +dz ) ; 
      gc[ 6 ] = GlobalPoint( +dx, +dy, +dz ) ; 
      gc[ 7 ] = GlobalPoint( +dx, -dy, +dz ) ; 

      for( unsigned int i ( 0 ) ; i != 8 ; ++i )
      {
	 lc[i] = HepPoint3D( gc[i].x(), gc[i].y(), gc[i].z() ) ;
      }

      ref   = 0.25*( lc[0] + lc[1] + lc[2] + lc[3] ) ;
      return lc ;
   }

   const CaloCellGeometry::CornersVec& 
   IdealCastorTrapezoid::getCorners() const 
   {
      const CornersVec& co ( CaloCellGeometry::getCorners() ) ;
//      std::cout<<"about to check for empty corners? empty = "<<(co.empty()?"true":"false")<<std::endl ;
      if( co.uninitialized() ) 
      {
//      std::cout<<"about to call setCorners"<<std::endl ;
	 CaloCellGeometry::CornersVec& corners ( setCorners() ) ;
//      std::cout<<"about to call getposition"<<std::endl ;
	 const GlobalPoint& p ( getPosition() ) ;
	 const float xx ( p.x() ) ;
	 const float yy ( p.y() ) ;
	 const float zz ( p.z() ) ;
//      std::cout<<"about to fill zero position"<<std::endl ;
	 corners[ 0 ] = GlobalPoint( xx-dx(), yy-dy(), zz-dz() ) ; 
//      std::cout<<"about to fill 1 position"<<std::endl ;
	 corners[ 1 ] = GlobalPoint( xx-dx(), yy+dy(), zz-dz() ) ; 
	 corners[ 2 ] = GlobalPoint( xx+dx(), yy+dy(), zz-dz() ) ; 
	 corners[ 3 ] = GlobalPoint( xx+dx(), yy-dy(), zz-dz() ) ; 
	 corners[ 4 ] = GlobalPoint( xx-dx(), yy-dy(), zz+dz() ) ; 
	 corners[ 5 ] = GlobalPoint( xx-dx(), yy+dy(), zz+dz() ) ; 
	 corners[ 6 ] = GlobalPoint( xx+dx(), yy+dy(), zz+dz() ) ; 
	 corners[ 7 ] = GlobalPoint( xx+dx(), yy-dy(), zz+dz() ) ; 
      }
      return co ;
   }

   bool 
   IdealCastorTrapezoid::inside( const GlobalPoint& point ) const 
   {
      bool is_inside ( false ) ;

/*      const GlobalPoint& face ( getPosition() ) ;

      if( fabs( point.x() - face.x() ) <= dx()/2   &&
	  fabs( point.y() - face.y() ) <= sin( an() )*dy()/2 )
      {
	 const float sl   ( tan( an() ) ) ;
	 const float blow ( face.y() - sl*face.z() ) ;

	 const float sign ( 0 < point.z() ? 1 : -1 ) ;
	 const float bhigh ( face.y() - sl*sign*( face.z() + sign*dz() ) ) ;

	 is_inside = ( ( point.z() >  sign*( point.y() - blow  )/sl )  &&
		       ( point.z() <= sign*( point.y() - bhigh )/sl )     ) ;
		       }*/
      return is_inside;
   }

   std::ostream& operator<<( std::ostream& s, const IdealCastorTrapezoid& cell ) 
   {
      s << "Center: " <<  cell.getPosition() << std::endl ;
      s 	 << ", dx = " << cell.dx() 
//<< "TiltAngle = " << cell.an() 
	<< ", dy = " << cell.dy() << ", dz = " << cell.dz() << std::endl ;
      return s;
   }
}
