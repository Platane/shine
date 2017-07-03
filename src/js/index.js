import * as parsing from './parsing';
import * as style from './style';
import * as dom from './dom';

const ex = { ...parsing, ...style, ...dom };

Object.keys(ex).forEach(key => (window[key] = ex[key]));
