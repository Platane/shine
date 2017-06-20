let component =
  ReasonReact.statelessComponent "Badge"; /* let createZonePaths =
  List.map2 (
    fun polygon fill => <Zone polygon fill />
  );  */

let createZonePaths zones colors => [<Zone polygon=(List.hd zones) fill=(List.hd colors) />];

let make ::zones ::colors _children => {
  /* let make zones::(zones: list polygon) colors::(colors: list string) _children => { */
  ...component,
  render: fun () _self => {
    let u = 1 + 1;
    let firstZone = List.hd zones;
    let zonePaths = createZonePaths zones colors;
    <svg viewBox="0 0 100 100"> (ReasonReact.arrayToElement (Array.of_list zonePaths)) </svg>
  }
};
