import * as parsing from './parsing';
import * as style from './style';

const ex = { ...parsing, ...style };

Object.keys(ex).forEach(key => (window[key] = ex[key]));
