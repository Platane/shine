open Type;

let style = Common.getClassName "badgeEditor";


let applyTranform_to_point : ( float, point ) => point => point = fun ( a, b ) p =>
  {
    x: a *. p.x +. b.x,
    y: a *. p.y +. b.y,
  };


let resizeZone_to_zone : ( float, point ) => zone => zone = fun transform zone =>
  {
    vertices : List.map ( applyTranform_to_point transform ) zone.vertices,
    center: applyTranform_to_point transform zone.center,
    normal: zone.normal,
    path: "",
  };

let transform_box : box => box => ( float, point ) = fun source target => {

  let dim : box => point = fun box => Point.sub box.max box.min;

  let dim_target = dim target;
  let dim_source = dim source;

  let a = min ( dim_target.x /. dim_source.x ) ( dim_target.y /. dim_source.y );

  let margin = Point.scale (Point.sub dim_target (Point.scale dim_source a)) 0.5;

  let b = Point.sub target.min (Point.scale source.min a) |> Point.add margin;

  ( a, b )
};


type state = {
  hovered: int
};

let component = ReasonReact.statelessComponent "BadgeEditor";

let make zones::(zones: list zone) lightSource::(lightSource: point) _children => {

  ...component,

  render: fun _state _self => {

    let colors =
      List.map
        (fun zone => Illuminate.computeColor zone lightSource)
        zones;


    let extractVertices: Type.zone => Type.polygon = fun zone => zone.vertices;

    let source = List.map extractVertices zones |> List.flatten |> Point.boundingBox;

    let target : box = {
      max: { x:200.0,y:200.0 },
      min: { x:-200.0,y:-200.0 },
    };

    let viewport: box = {
      max: { x:250.0,y:250.0 },
      min: { x:-250.0,y:-250.0 },
    };

    let zones_ = zones |> List.map ( resizeZone_to_zone ( transform_box source target ) );

    <div className=( style "container" )>
        <Canvas viewport=viewport >
          <Arrow b=lightSource a={x:0.0, y:0.0} />
          <Zones colors zones=zones_ />
          <Normals zones=zones_ />
          <LightSource lightSource />
        </Canvas>
    </div>
  }
};