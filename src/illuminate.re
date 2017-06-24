/* compute colors of each zones, depending of the zone position, the zone normal and the lightSource */
let computeColors (badge: Type.badge, _lightSource: Type.point) =>
  List.map (fun _a => "red") badge.zones;



let computeDefaultNormals zones => List.map (fun _a => ({x: 1.0, y: 0.0}: Type.point)) zones;
